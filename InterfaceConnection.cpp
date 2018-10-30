
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

long connect(string server, string uid, string pwd)
{

    SRVR_CONNECT_HDL *jdbcConnect = NULL;

    SQLRETURN rc;

    // Initialize gDescItems array
    initSqlCore(0, NULL);

    jdbcConnect = new SRVR_CONNECT_HDL();
    rc = jdbcConnect->sqlConnect("db__root", "123");

    switch (rc)
    {
    case SQL_SUCCESS:
        break;
    case SQL_SUCCESS_WITH_INFO:

        break;
    default:
        break;
    }

    return rc;

}

