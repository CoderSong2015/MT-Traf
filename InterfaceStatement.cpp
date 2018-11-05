#include "InterfaceStatement.h"


void ExecuteDirect(string server,
              long dialogueId,
              int txid,
              bool autoCommit,
              int txnMode,
              string stmtLabel,
              string cursorName,
              string sql,
              bool isSelect,
              int queryTimeout,
              int holdability,
              long currentStmtId){
        ExceptionStruct                         exception_;
        long                                    estimatedCost;
        long                                    rowsAffected;
        ERROR_DESC_LIST_def                     sqlWarning;
        SQLItemDescList_def                     outputDesc;
        jint                                            currentTxid = txid;
        jint                                            externalTxid = 0;
        long                                            stmtId;

        char              *nSql = NULL;
        char              *nStmtLabel = NULL;
        char              *nCursorName = NULL;
        jbyteArray              sqlByteArray;
        jboolean                isCopy;
        jsize                   len;
        SQLValue_def    sqlString;
        short                   txn_status;

        sqlString.dataCharset = 0;
        sqlString.dataInd = 0;
        sqlString.dataType = SQLTYPECODE_VARCHAR;

        if (!sql.empty())
        {
                nSql = new char[sql.length() + 1];
                std::strcpy (nSql, sql.c_str());
                sqlString.dataValue._buffer = (unsigned char *)nSql;
                sqlString.dataValue._length = strlen(nSql);
                DEBUG_OUT(DEBUG_LEVEL_CLI,("sqlString = '%s', length =%ld", nSql, len));
                MEMORY_DUMP(DEBUG_LEVEL_CLI, nSql, len);
        }
        else{
            FUNCTION_RETURN_VOID(("sql is NULL"));
        }

        if (!stmtLabel.empty()){
                nStmtLabel = new char[stmtLabel.length() + 1];
                std::strcpy (nStmtLabel, stmtLabel.c_str());
        }else{
            if(NULL != nSql){
                delete[] nSql;
            }
            FUNCTION_RETURN_VOID(("stmtLabel is NULL"));
        }

        if (!cursorName.empty()){
            nCursorName = new char[cursorName.length() + 1];
            std::strcpy (nCursorName, cursorName.c_str());
        }

        else{
            nCursorName = NULL;
        }

        txn_status = 0;
        /* do not be defined in sqlmxcommonfunctions in t2
        if ((txn_status = beginTxnControl(jenv, currentTxid, externalTxid, txnMode, -1) != 0))
        {
                jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
                throwTransactionException(jenv, txn_status);
                FUNCTION_RETURN_VOID(("beginTxnControl() failed"));
        }*/

        exception_.u.SQLError.errorList._buffer = NULL;
        odbc_SQLSvc_ExecDirect_sme_(NULL, NULL,
                        &exception_,
                        dialogueId,
                        nStmtLabel,
                        (char *)nCursorName,
                        "",                                     // StmtExplainName
                        EXTERNAL_STMT,
                        (isSelect ? TYPE_SELECT : TYPE_UNKNOWN),
                        &sqlString,
                        holdability,
                        queryTimeout,
                        &estimatedCost,
                        &outputDesc,
                        &rowsAffected,
                        &sqlWarning,
                        &stmtId,
                        currentStmtId);

        if (NULL != nSql)
                delete[] nSql;
        if (NULL != nStmtLabel)
                delete[] nStmtLabel;
        if (NULL != nCursorName)
                delete[] nCursorName;

        txn_status = 0;
        /*
        if ((txn_status = endTxnControl(jenv, currentTxid, txid, autoCommit,
                                                exception_.exception_nr, isSelect, txnMode, externalTxid)) != 0)
        {
                jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
                throwTransactionException(jenv, txn_status);
                FUNCTION_RETURN_VOID(("endTxnControl() Failed"));
        }*/
        switch (exception_.exception_nr)
        {
        case CEE_SUCCESS:
                //if (sqlWarning._length != 0)
                //        setSQLWarning(jenv, jobj, &sqlWarning);
                //setExecuteDirectOutputs(jenv, jobj, &outputDesc, rowsAffected, currentTxid, stmtId);
                break;
        case odbc_SQLSvc_ExecDirect_ParamError_exn_:
                break;
        case odbc_SQLSvc_ExecDirect_SQLError_exn_:
                break;
        case odbc_SQLSvc_ExecDirect_SQLQueryCancelled_exn_:
                break;
        case odbc_SQLSvc_ExecDirect_SQLInvalidHandle_exn_:
                break;
        case odbc_SQLSvc_ExecDirect_SQLStillExecuting_exn_:
        case odbc_SQLSvc_ExecDirect_InvalidConnection_exn_:
        case odbc_SQLSvc_ExecDirect_TransactionError_exn_:
        default:
// TFDS - These error should not happen
                break;
        }
        FUNCTION_RETURN_VOID((NULL));
}

