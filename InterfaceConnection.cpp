
#include <platform_ndcs.h>
#include <sql.h>
#include <sqlext.h>
#include "JdbcDriverGlobal.h"
#include "InterfaceConnection.h"
#include "InterfaceCommonFunctions.h"
#include "CoreCommon.h"
#include "SrvrCommon.h"
#include "SrvrOthers.h"
#include "CSrvrConnect.h"
#include "Debug.h"
#include "GlobalInformation.h"
#include "sqlcli.h"
#include <iostream>


long interface::Connect(string server, string uid, string pwd)
{

    SRVR_CONNECT_HDL *pConnect = NULL;

    SQLRETURN rc;

    // Initialize gDescItems array
    initSqlCore(0, NULL);

    MEMORY_ALLOC_OBJ(pConnect, SRVR_CONNECT_HDL());
    rc = pConnect->sqlConnect("db__root", "123");

    switch (rc)
    {
    case SQL_SUCCESS:
        std::cout << "success" << std::endl;
        break;
    case SQL_SUCCESS_WITH_INFO:
        break;
    default:
        std::cout << "error" << std::endl;
        break;
    }

    return (long)pConnect;

}

long interface::ConnectionClose(string server, long dialogueId)
{

    SRVR_CONNECT_HDL *pConnect;
    SQLRETURN rc;

    ExceptionStruct setConnectException;
    ERROR_DESC_LIST_def sqlWarning;
    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                 &setConnectException,
                 dialogueId,
                 END_SESSION,
                 0,
                 NULL,
                 &sqlWarning);
    if (setConnectException.exception_nr != CEE_SUCCESS)
    {
       // throwSetConnectionException(jenv, &setConnectException);
        return setConnectException.exception_nr;
    }

    pConnect = (SRVR_CONNECT_HDL *)dialogueId;
    rc = pConnect->sqlClose();
    switch (rc)
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            //setSQLWarning(jenv, jcls, &pConnect->sqlWarning);
            pConnect->cleanupSQLMessage();
            break;
        default:
        //throwSQLException(jenv, pConnect->getSQLError());
            pConnect->cleanupSQLMessage();
            break;
    }
    MEMORY_DELETE_OBJ(pConnect);
    return rc;
}

void setConnectAttr(string server, long dialogueId,
        short attribute, SQLUINTEGER valueNum, const char *valuePtr) {

    ExceptionStruct exception_;
    ERROR_DESC_LIST_def sqlWarning;
    long sts;
    const char *nServer = NULL;

    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL, &exception_, dialogueId,
            attribute, valueNum, (char *) valuePtr, &sqlWarning);
    switch (exception_.exception_nr) {
    case CEE_SUCCESS:
        break;
    case odbc_SQLSvc_SetConnectionOption_SQLError_exn_:
        //throwSQLException(jenv, &exception_.u.SQLError);
        break;
    default:
        //throwSQLException(jenv, PROGRAMMING_ERROR, NULL, "HY000",
        //        exception_.exception_nr);
        break;
    }
    FUNCTION_RETURN_VOID((NULL));
}

void setCatalog(string server, long dialogueId, string catalog)
{
    char *nCatalog = NULL;
    nCatalog = new char[catalog.length() + 1];
    std::strcpy (nCatalog, catalog.c_str());

    setConnectAttr(server, dialogueId, SQL_ATTR_CURRENT_CATALOG, 0, nCatalog);

    if(NULL != nCatalog){
        delete[] nCatalog;
    }
    FUNCTION_RETURN_VOID((NULL));
}

void interface::ConnectionInit(std::string server,
                               long dialogueId,
                               std::string catalog,
                               std::string schema,
                               std::string mploc,
                               bool isReadOnly,
                               bool autoCommit,
                               int transactionIsolation,
                               int loginTimeout,
                               int queryTimeout,
                               std::string modulecaching,
                               std::string compiledmodulelocation,
                               bool blnDoomUsrTxn,
                               int statisticsIntervalTime,
                               int statisticsLimitTime,
                               std::string statisticsType,
                               std::string programStatisticsEnabled,
                               std::string statisticsSqlPlanEnabled)
{
    //need to add mutex because use srvrGlobal
/*
    FUNCTION_ENTRY("Java_org_apache_trafodion_jdbc_t2_SQLMXConnection_connectInit",("..."));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  jenv=0x%08x, server=%s, dialogueId=0x%08x",
                    jenv,
                    DebugJString(jenv,server),
                    dialogueId));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  catalog=%s",
                    DebugJString(jenv,catalog)));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  schema=%s",
                    DebugJString(jenv,schema)));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  mploc=%s",
                    DebugJString(jenv,mploc)));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  isReadOnly=%d, transactionIsolation=%ld",
                    isReadOnly,
                    transactionIsolation));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  loginTimeout=%ld, queryTimeout=%ld",
                    loginTimeout,
                    queryTimeout));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  statisticsIntervalTime=%ld, statisticsLimitTime=%ld, statisticsType=%s, programStatisticsEnabled=%s, statisticsSqlPlanEnabled=%s",
                    statisticsIntervalTime,
                    statisticsLimitTime,
                    DebugJString(jenv,statisticsType),
                    DebugJString(jenv,programStatisticsEnabled),
                    DebugJString(jenv,statisticsSqlPlanEnabled)
            ));

    //MFC - new properties
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  MFC modulecaching=%s",
                    DebugJString(jenv,modulecaching)));
    DEBUG_OUT(DEBUG_LEVEL_ENTRY,("  MFC compiledmodulelocation=%s",
                    DebugJString(jenv,compiledmodulelocation)));
*/

    const char *nCatalog;
    const char *nSchema;
    const char *nMploc;
    jthrowable exception;

// MFC - new properties
    const char *nModuleCaching;
    const char *nCompiledModuleLocation;

    // PUBLISHING
    const char *nStatisticsType;
    const char *nProgramStatisticsEnabled;
    const char *nStatisticsSqlPlanEnabled;




    ExceptionStruct setConnectException;
    ERROR_DESC_LIST_def sqlWarning;

    // Debug checking if sqlStmtType enum's (in sqlcli.h) do not match those
    // defined in SQLMXConnection.java.  This is added as a safety means to detect
    // if they get out of sync with each other and exit. Furthermore, this will
    // get detected only during new development efforts and will not occur in the field.
    DEBUG_ASSERT(org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL == SQL_CONTROL, ("Mismatch on SQL_CONTROL enum sql stmt type"));
    DEBUG_ASSERT(org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION == SQL_SET_TRANSACTION, ("Mismatch on SQL_SET_TRANSACTION enum sql stmt type"));
    DEBUG_ASSERT(org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG == SQL_SET_CATALOG, ("Mismatch on SQL_SET_CATALOG enum sql stmt type"));
    DEBUG_ASSERT(org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA == SQL_SET_SCHEMA, ("Mismatch on SQL_SET_SCHEMA enum sql stmt type"));

#ifdef _DEBUG
    if((org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL != SQL_CONTROL) ||
            (org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION != SQL_SET_TRANSACTION ) ||
            (org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG != SQL_SET_CATALOG) ||
            (org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA != SQL_SET_SCHEMA))
    {
        printf("The SQLATTR_QUERY_TYPE enum's do not match to values defined in SQLMXConnection.\n");
        exit(1);
    }
#endif

    if (!catalog.empty())
    nCatalog = catalog.c_str();
    if (!schema.empty())
    nSchema = schema.c_str();
    if (!mploc.empty())
    nMploc = mploc.c_str();

    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
            &setConnectException,
            dialogueId,
            SET_JDBC_PROCESS,
            0,
            NULL,
           &sqlWarning);

    if (setConnectException.exception_nr != CEE_SUCCESS)
    {
        //throwSetConnectionException(jenv, &setConnectException);
        FUNCTION_RETURN_VOID(("SET_JDBC_PROCESS - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                        CliDebugSqlError(setConnectException.exception_nr)));
    }

#if 0 /* NOT NEEDED with improvements to Native Expressions code */
    // new code begin: to disable native code for multi-threading
    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
            &setConnectException,
            dialogueId,
            CQD_PCODE_OFF,
            0,
            NULL,
            &sqlWarning);
    if (setConnectException.exception_nr != CEE_SUCCESS)
    {
        throwSetConnectionException(jenv, &setConnectException);
        FUNCTION_RETURN_VOID(("CQD_PCODE_OFF - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                        CliDebugSqlError(setConnectException.exception_nr)));
    }
    // new code end
#endif /* NOT NEEDED with improvements to Native Expressions code */

    if (srvrGlobal->nowaitOn == 2)
    {
        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SET_OLT_QUERY_OPT,
                0,
                NULL,
                &sqlWarning);
        if (setConnectException.exception_nr != CEE_SUCCESS)
        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SET_OLT_QUERY_OPT - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
    }
    /*
   if (NULL != nMploc)
    {
        //Solution 10-120315-2068 --- start
        /*
         The SET NAMETYPE statement sets the NAMETYPE attribute value for the current
         SQL session.
         The SET NAMETYPE statement sets the NAMETYPE attribute for all dynamic
         statements within the control flow scope of an embedded SQL program for the current
         SQL session.
         SET NAMETYPE is an SQL/MX extension.
         ANSI | NSK
         specifies whether the system assumes logical names (ANSI) or physical Guardian
         names (NSK) are used to reference SQL/MP database objects in SQL statements
         */
       /*
        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SET_NAMETYPE,
                0,
                "NSK",
                &sqlWarning);
        if (setConnectException.exception_nr != CEE_SUCCESS)
        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SET_MPLOC - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }

        //Solution 10-120315-2068 --- end

        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SET_MPLOC,
                0,
                (char *)nMploc,
                &sqlWarning);
       if (setConnectException.exception_nr != CEE_SUCCESS)
        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SET_MPLOC - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
    }
    */

    if (NULL != nCatalog)
    {
        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SET_CATALOG,
                0,
                (char *)nCatalog,
                &sqlWarning);
        //JNI_ReleaseStringUTFChars(jenv,catalog, nCatalog);

        if (setConnectException.exception_nr != CEE_SUCCESS)
        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SET_CATALOG - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
    }
    else
    {
        strcpy(srvrGlobal->CurrentCatalog, "SEABASE");
    }

    if (NULL != nSchema)
    {

        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SET_SCHEMA,
                0,
                (char *)nSchema,
                &sqlWarning);
        //JNI_ReleaseStringUTFChars(jenv,schema, nSchema);

       if (setConnectException.exception_nr != CEE_SUCCESS)
        {
//            throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SET_SCHEMA - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
    }
    else
    {
        strcpy(srvrGlobal->CurrentSchema, "SEABASE");

    }

    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                 &setConnectException,
                 dialogueId,
                 BEGIN_SESSION,
                 0,
                 NULL,
                 &sqlWarning);
    if (setConnectException.exception_nr != CEE_SUCCESS)
    {
        //throwSetConnectionException(jenv, &setConnectException);
        FUNCTION_RETURN_VOID(("BEGIN_SESSION - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                        CliDebugSqlError(setConnectException.exception_nr)));
    }
   if(blnDoomUsrTxn)
    {

        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                CQD_DOOM_USER_TXN,
                0,
                NULL,
                &sqlWarning);
        if (setConnectException.exception_nr != CEE_SUCCESS)
        {
//            throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("CQD_DOOM_USER_TXN - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
    }

    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
            &setConnectException,
            dialogueId,
            SQL_TXN_ISOLATION,
            transactionIsolation,
            NULL,
            &sqlWarning
    );

    if (setConnectException.exception_nr != CEE_SUCCESS)
    {
        //throwSetConnectionException(jenv, &setConnectException);
        FUNCTION_RETURN_VOID(("SQL_TXN_ISOLATION - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                        CliDebugSqlError(setConnectException.exception_nr)));
    }

    odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
            &setConnectException,
            dialogueId,
            SQL_AUTOCOMMIT,
            autoCommit,
            NULL,
            &sqlWarning
    );

   if (setConnectException.exception_nr != CEE_SUCCESS)
    {
        //throwSetConnectionException(jenv, &setConnectException);
        FUNCTION_RETURN_VOID(("SQL_AUTOCOMMIT - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                        CliDebugSqlError(setConnectException.exception_nr)));
    }
    // MFC if mfc is on set the recompilation warnings on
    // to help remove stale modules
    if (srvrGlobal->moduleCaching == 1)
    {
        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,
                &setConnectException,
                dialogueId,
                SQL_RECOMPILE_WARNING,
                0,
                NULL,
                &sqlWarning
        );

        if (setConnectException.exception_nr != CEE_SUCCESS)
        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("SQL_RECOMPILE_WARNING - setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                            CliDebugSqlError(setConnectException.exception_nr)));
        }
        //MFC support for BigNum
        odbc_SQLSvc_SetConnectionOption_sme_(NULL, NULL,&setConnectException,dialogueId,
                SET_SESSION_INTERNAL_IO,0,NULL,
                &sqlWarning);

        if (setConnectException.exception_nr != CEE_SUCCESS)

        {
            //throwSetConnectionException(jenv, &setConnectException);
            FUNCTION_RETURN_VOID(("Set Session internal_format_io failure setConnectException.exception_nr(%s) is not CEE_SUCCESS",
                           CliDebugSqlError(setConnectException.exception_nr)));

        }

    }

//    printf("Native statisticsIntervalTime :%ld\n", statisticsIntervalTime);
//    printf("Native statisticsLimitTime :%ld\n", statisticsLimitTime);

    if (!statisticsType.empty()) {
        nStatisticsType = statisticsType.c_str();
    }
    if (programStatisticsEnabled.empty()) {
        nProgramStatisticsEnabled = programStatisticsEnabled.c_str();
    }
    if (statisticsSqlPlanEnabled.empty()) {
        nStatisticsSqlPlanEnabled = statisticsSqlPlanEnabled.c_str();
    }

    SRVR_STMT_HDL *RbwSrvrStmt = NULL;
    SRVR_STMT_HDL *CmwSrvrStmt = NULL;
    const char    *rbwStmtStr  = "ROLLBACK WORK";
    const char    *cmwStmtStr  = "COMMIT WORK";
    int           stmtLen;
    long          sqlcode;

    SQLValue_def inputValue;
    SQLRETURN retCode;

    inputValue.dataCharset = 0;
    inputValue.dataInd = 0;
    inputValue.dataType = SQLTYPECODE_VARCHAR;
    inputValue.dataValue._length = 0;
    MEMORY_ALLOC_ARRAY(inputValue.dataValue._buffer, unsigned char, MAX_INTERNAL_STMT_LEN);
   if((RbwSrvrStmt = createSrvrStmt(
                    dialogueId,
                    "STMT_ROLLBACK_1",
                    &sqlcode,
                    NULL,
                    SQLCLI_ODBC_MODULE_VERSION,
                    0,
                    TYPE_UNKNOWN,
                    FALSE,
                    SQL_UNKNOWN,
                    TRUE,
                    0)) == NULL)
    {
        setConnectException.exception_nr = odbc_SQLSvc_Prepare_SQLInvalidHandle_exn_;
        setConnectException.u.SQLInvalidHandle.sqlcode = sqlcode;
        FUNCTION_RETURN_VOID(("createSrvrStmt() Failed"));
    }

    stmtLen = strlen(rbwStmtStr);
    strncpy((char*)inputValue.dataValue._buffer, rbwStmtStr, stmtLen);
    inputValue.dataValue._length = stmtLen;
    retCode = RbwSrvrStmt->Prepare(&inputValue, INTERNAL_STMT, CLOSE_CURSORS_AT_COMMIT, 0);
    if(retCode == SQL_ERROR)
    {
        setConnectException.exception_nr = odbc_SQLSvc_Prepare_SQLError_exn_;
        //setConnectException.u.SQLError = ;
        FUNCTION_RETURN_VOID(("Prepare ROLLBACK WORK Transaction Statement Failed"));
    }

    if((CmwSrvrStmt = createSrvrStmt(
                    dialogueId,
                    "STMT_COMMIT_1",
                    &sqlcode,
                    NULL,
                    SQLCLI_ODBC_MODULE_VERSION,
                    0,
                    TYPE_UNKNOWN,
                    FALSE,
                    SQL_UNKNOWN,
                    TRUE,
                    0)) == NULL)
    {
        setConnectException.exception_nr = odbc_SQLSvc_Prepare_SQLInvalidHandle_exn_;
        setConnectException.u.SQLInvalidHandle.sqlcode = sqlcode;
        FUNCTION_RETURN_VOID(("createSrvrStmt() Failed"));
    }

    stmtLen = strlen(cmwStmtStr);
    strncpy((char*)inputValue.dataValue._buffer, cmwStmtStr, stmtLen);
    inputValue.dataValue._length = stmtLen;
    retCode = CmwSrvrStmt->Prepare(&inputValue, INTERNAL_STMT, CLOSE_CURSORS_AT_COMMIT, 0);
    if(retCode == SQL_ERROR)
    {
        setConnectException.exception_nr = odbc_SQLSvc_Prepare_SQLError_exn_;
        //setConnectException.u.SQLError = ;
        FUNCTION_RETURN_VOID(("Prepare COMMIT WORK Transaction Statement Failed"));
    }

    // Assign the module Information
    nullModule.version = SQLCLI_ODBC_MODULE_VERSION;
    nullModule.module_name = NULL;
    nullModule.module_name_len = 0;
    nullModule.charset = "ISO88591";
    nullModule.creation_timestamp = 0;

    srvrGlobal->m_FetchBufferSize = MAX_FETCH_BUFFER_SIZE; //Defaulting set the fetch buffer size to 512K
    srvrGlobal->fetchAhead = false;
    srvrGlobal->enableLongVarchar = false;
    srvrGlobal->boolFlgforInitialization = 1;
    srvrGlobal->maxRowsFetched = 0;

    // temporary set buildId for non delay error mode for all connection.
    // should be changed once we use InterfaceConnection in java layer.
    srvrGlobal->drvrVersion.buildId = STREAMING_MODE | ROWWISE_ROWSET | CHARSET | PASSWORD_SECURITY;
   FUNCTION_RETURN_VOID((NULL));
}
