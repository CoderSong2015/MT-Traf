
void prepare(string server,
             long dialogueId,
             int txid,
             bool autoCommit,
             std::string stmtLabel,
             std::string sql,
             bool isSelect,
             int queryTimeout,
             int holdability,
             int batchSize,
             int fetchSize)
{
    FUNCTION_ENTRY("Java_org_apache_trafodion_jdbc_t2_SQLMXPreparedStatement_prepare",("..., isSelect=%d, batchSize=%ld, fetchSize=%ld, ...",
                   isSelect,
                   batchSize,
                   fetchSize));

    long                                    estimatedCost;
    long                                    inputParamOffset;
    ERROR_DESC_LIST_def                     sqlWarning;
    SQLItemDescList_def                     outputDesc;
    SQLItemDescList_def                     inputDesc;
    jint                                            currentTxid = txid;
    jbyteArray                                      sqlByteArray;
    jboolean                                        isCopy;
    jsize                                           len;
    SQLValue_def                            sqlString;



    long                                            stmtId;

    ExceptionStruct exception_;
    CLEAR_EXCEPTION(exception_);

    sqlString.dataCharset = 0;
    sqlString.dataInd = 0;
    sqlString.dataType = SQLTYPECODE_VARCHAR;

    char *nSql = NULL;
    if (!sql.empty())
    {
        nSql = new char [sql.length()+1];
        std::strcpy (nSql, sql.c_str());
        len = strlen(nSql);
        //Start Soln. No.: 10-091103-5969 --- commented this fix
        //sqlString.dataValue._buffer = new unsigned char [len+1];
        //memset(sqlString.dataValue._buffer,'\0',len+1);
        //strncpy(sqlString.dataValue._buffer,nSql,len);
        sqlString.dataValue._buffer = (unsigned char *)nSql;
        //End Soln. No.: 10-091103-5969
        sqlString.dataValue._length = len;
    }
    else
    {
        //throwSQLException(jenv, INVALID_SQL_STRING_ERROR, NULL, "HY090");
        FUNCTION_RETURN_VOID(("Null SQL string"));
    }

    char *nStmtLabel = NULL;
    if (!stmtLabel.empty())
        nStmtLabel = new char [stmtLabel.length()+1];
        std::strcpy (nStmtLabel, stmtLabel.c_str());
        len = strlen(nStmtLabel);
    else
    {

        delete nSql;
        FUNCTION_RETURN_VOID(("Null Statement Label"));
    }
    // Note: WLI V31 RFE, see Sol: 10-040311-4065 -
    // Resolve an 'Invalid Transaction state' error when the App server
    // switches to external transaction mode without committing the
    // transaction. Prior to this RFE prepares where done within a
    // transaction started by either JDBC/MX or the application.

    odbc_SQLSvc_Prepare_sme_(NULL, NULL,
                             &exception_,
                             dialogueId,
                             nStmtLabel,
                             "",                                     // StmtExplainName
                             EXTERNAL_STMT,
                             &sqlString,
                             holdability,
                             (isSelect ? TYPE_SELECT : TYPE_UNKNOWN),
                             batchSize,
                             fetchSize,
                             queryTimeout,
                             &estimatedCost,
                             &inputDesc,
                             &outputDesc,
                             &sqlWarning,
                             &stmtId,
                             &inputParamOffset,
                             NULL,//MFC
                             FALSE);

    if(NULL != nSql){
        delete nSql;
    }
    if(NULL != nStmtLabel){
        delete nStmtLabel;
    }

    switch (exception_.exception_nr)
    {
    case CEE_SUCCESS:
        //setPrepareOutputs(jenv, jobj, &inputDesc, &outputDesc, currentTxid, stmtId, inputParamOffset);
        //if (sqlWarning._length > 0)
         //   setSQLWarning(jenv, jobj, &sqlWarning);
        break;
    case odbc_SQLSvc_Prepare_SQLQueryCancelled_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, QUERY_CANCELLED_ERROR, NULL, "HY008",
        //                  exception_.u.SQLQueryCancelled.sqlcode);
        break;
    case odbc_SQLSvc_Prepare_SQLError_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, &exception_.u.SQLError);
        break;
    case odbc_SQLSvc_Prepare_ParamError_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, PROGRAMMING_ERROR, exception_.u.ParamError.ParamDesc, "HY000");
        break;
    case odbc_SQLSvc_Prepare_SQLInvalidHandle_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, INVALID_HANDLE_ERROR, NULL, "HY000", exception_.u.SQLInvalidHandle.sqlcode);
        break;
    case odbc_SQLSvc_Prepare_SQLStillExecuting_exn_:
    case odbc_SQLSvc_Prepare_InvalidConnection_exn_:
    case odbc_SQLSvc_Prepare_TransactionError_exn_:
    default:
        // TFDS - These exceptions should not happen
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, PROGRAMMING_ERROR, NULL, "HY000", exception_.exception_nr);
        break;
    }
    FUNCTION_RETURN_VOID((NULL));
}

void execute(string server,
             long dialogueId,
             int txid,
             boolean autoCommit,
             int txnMode,
             long stmtId,
             string cursorName,
             bool isSelect,
             long inputRowCnt,
             long inValuesLength,
             char *inValues,
             int queryTimeout,
             bool isAnyLob,
             string iso88591Encoding,
             object resultSet,
             bool contBatchOnError){
    ERROR_DESC_LIST_def     sqlWarning;
    jint                            paramRowNumber;
    jint                            currentTxid = txid;
    jint                            externalTxid = 0;

    long                            sqlcode;
    SRVR_STMT_HDL           *pSrvrStmt;
    //jthrowable                    queuedException = NULL;
    jthrowable          exceptionHead = NULL;// RFE: Batch update improvements

    CLEAR_WARNING(sqlWarning);

    if ((pSrvrStmt = getSrvrStmt(dialogueId, stmtId, &sqlcode)) == NULL)
    {
        //throwSQLException(jenv, INVALID_HANDLE_ERROR, NULL, "HY000", sqlcode);
        FUNCTION_RETURN_VOID(("getSrvrStmt() Failed"));
    }

    if (paramRowCount==0)
    {
        // No rows to process.  Return nothing.
        //setExecuteOutputs(jenv, jobj, pSrvrStmt, NULL, 0, currentTxid);
        FUNCTION_RETURN_VOID(("paramRowCount==0"));
    }
    SQLValueList_def        outSqlValueList;                // Ouput SQL Value list
    CLEAR_LIST(outSqlValueList);
    SQLValueList_def        inSqlValueList;                 // Input SQL Value list
    CLEAR_LIST(inSqlValueList);
    ROWS_COUNT_LIST_def                     rowCount;
    CLEAR_LIST(rowCount);
    ExceptionStruct exception_;
    CLEAR_EXCEPTION(exception_);


    const char *nCursorName = NULL;
    if (!cursorName.empty())
    {
        nCursorName = new char [cursorName.length()+1];
        std::strcpy (nCursorName, cursorName.c_str());
    }

    inSqlValueList->_buffer = inValues;
    inSqlValueList->_length = inValuesLength;

    // Save the result set for the returned row data
    pSrvrStmt->resultSetObject = resultSet;

    MEMORY_ALLOC_ARRAY(rowCount._buffer,int,paramRowCount);
    memset(rowCount._buffer,0,paramRowCount*sizeof(int));
    rowCount._length = 0;
    pSrvrStmt->totalRowCount = 0;

    // If execute call fails, will be set to failure.
    // All other failures are handled by success processing.
    exception_.exception_nr = CEE_SUCCESS;

    int errorRow = 0;
    int rowsExecuted = 0;

    short txn_status = 0;

    long totalRows = inputRowCnt;
    if (totalRows)
    {
        // Try to execute the statements
        odbc_SQLSvc_ExecuteN_sme_(NULL, NULL,
        &exception_,
        dialogueId,
        stmtId,
        (char *)nCursorName,
        (isSelect ? TYPE_SELECT : TYPE_UNKNOWN),
        totalRows,
        &inSqlValueList,
        FALSE,
        queryTimeout,
        &outSqlValueList,
        &sqlWarning);

        DEBUG_OUT(DEBUG_LEVEL_DATA,("outSqlValueList._buffer=0x%08x, outSqlValueList._length=0x%08x",
        outSqlValueList._buffer,
        outSqlValueList._length));
       /*
        if (pSrvrStmt->rowCount._length)
        {
            // Row count information returned.  Append to existing row count information.
            rowsExecuted = pSrvrStmt->rowCount._length;
            rowCount._length += pSrvrStmt->rowCount._length;
            DEBUG_ASSERT(rowCount._length<=paramRowCount,
            ("rowCount._length(%ld)>paramRowCount(%ld)", rowCount._length, paramRowCount));
            memcpy(rowCount._buffer+paramRowNumber,
            pSrvrStmt->rowCount._buffer,
            sizeof(rowCount._buffer[0]) * pSrvrStmt->rowCount._length);
        }
        else if(contBatchOnError && paramRowCount > 2)
        {

            rowsExecuted = totalRows;
        }
        else
        {
            rowsExecuted = 1;
        }
        */
    }
    //}
    // Process the execute result.

    switch (exception_.exception_nr)
    {
    case CEE_SUCCESS:
        //if (sqlWarning._length > 0) setSQLWarning(jenv, jobj, &sqlWarning);
        /* RFE: Batch update improvements
        * Any queued exception will now be thrown in the end.
        */
        break;
    case odbc_SQLSvc_ExecuteN_SQLNoDataFound_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidRSMethodId, currentTxid);
        break;
    case odbc_SQLSvc_ExecuteN_SQLQueryCancelled_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, QUERY_CANCELLED_ERROR, NULL, "HY008",
       // exception_.u.SQLQueryCancelled.sqlcode);
        break;
    case odbc_SQLSvc_ExecuteN_SQLError_exn_:
    case odbc_SQLSvc_ExecuteN_SQLRetryCompile_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, &exception_.u.SQLError);
        break;
    case odbc_SQLSvc_ExecuteN_ParamError_exn_:
        //jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, PROGRAMMING_ERROR, exception_.u.ParamError.ParamDesc, "HY000");
        break;
    case odbc_SQLSvc_ExecuteN_SQLInvalidHandle_exn_:
       // jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
        //throwSQLException(jenv, INVALID_HANDLE_ERROR, NULL, "HY000",
        //exception_.u.SQLInvalidHandle.sqlcode);
        break;
    case odbc_SQLSvc_ExecuteN_SQLStillExecuting_exn_:
    case odbc_SQLSvc_ExecuteN_InvalidConnection_exn_:
    case odbc_SQLSvc_ExecuteN_TransactionError_exn_:
    case odbc_SQLSvc_ExecuteN_SQLNeedData_exn_:
    default:
        // TFDS - These exceptions should not happen
       // jenv->CallVoidMethod(jobj, gJNICache.setCurrentTxidStmtMethodId, currentTxid);
       // throwSQLException(jenv, PROGRAMMING_ERROR, NULL, "HY000", exception_.exception_nr);
        break;
    }

    // Free up the cursor name
    if(nCursorName)
    {
        delete nCursorName;
    }
    // If there was a parameter error, return null row counts.
    // Note: This is not how ODBC handles errors.  This handling many need to be changed
    //         in the future to match ODBC (return a row count array with error rows).  The
    //         current JDBC implementation is designed to make the change to the ODBC implemenation
    //         easier if required.

    /* RFE: Batch update improvements
    * Now returns the row count array with error rows.
    */
    // setExecuteOutputs(jenv, jobj, pSrvrStmt, &rowCount, pSrvrStmt->totalRowCount, currentTxid);
    /* RFE: Batch update improvements
    * Throw the queued exceptions if any
    */
    // if(exceptionHead)
    //        jenv->Throw(exceptionHead);

    MEMORY_DELETE(rowCount._buffer);
    FUNCTION_RETURN_VOID((NULL));
}


