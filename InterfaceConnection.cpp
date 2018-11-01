
#include <platform_ndcs.h>
#include <sql.h>
#include <sqlext.h>
#include "JdbcDriverGlobal.h"
#include "InterfaceConnection.h"
#include "SQLMXCommonFunctions.h"
#include "CoreCommon.h"
#include "SrvrCommon.h"
#include "SrvrOthers.h"
#include "CSrvrConnect.h"
#include "Debug.h"
#include "GlobalInformation.h"
#include "sqlcli.h"
#include <iostream>
long Connect(string server, string uid, string pwd)
{

    SRVR_CONNECT_HDL *jdbcConnect = NULL;

    SQLRETURN rc;

    // Initialize gDescItems array
    initSqlCore(0, NULL);

    MEMORY_ALLOC_OBJ(jdbcConnect, SRVR_CONNECT_HDL());
    rc = jdbcConnect->sqlConnect("db__root", "123");

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

    return (long)jdbcConnect;

}

long ConnectionClose(string server, long dialogueId)
{

    SRVR_CONNECT_HDL *jdbcConnect;
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

    jdbcConnect = (SRVR_CONNECT_HDL *)dialogueId;
    rc = jdbcConnect->sqlClose();
    switch (rc)
    {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            //setSQLWarning(jenv, jcls, &jdbcConnect->sqlWarning);
            jdbcConnect->cleanupSQLMessage();
            break;
        default:
        //throwSQLException(jenv, jdbcConnect->getSQLError());
            jdbcConnect->cleanupSQLMessage();
            break;
    }
    MEMORY_DELETE_OBJ(jdbcConnect);
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
    const char *nCatalog = NULL;
    nCatalog = catalog.c_str();

    setConnectAttr(server, dialogueId, SQL_ATTR_CURRENT_CATALOG, 0, nCatalog);

    FUNCTION_RETURN_VOID((NULL));
}

