#ifndef _INTERFACE_PREPARESTATEMENT_H_
#define _INTERFACE_PREPARESTATEMENT_H_


#include <platform_ndcs.h>
#ifdef NSK_PLATFORM
#include <sqlWin.h>
#include <windows.h>
#include <MD5.h>  // MFC
#else
#include <sql.h>
#endif
#include <sqlext.h>
#include "CoreCommon.h"
#include "JdbcDriverGlobal.h"
#include "org_apache_trafodion_jdbc_t2_SQLMXPreparedStatement.h"
#include "SQLMXCommonFunctions.h"
#ifdef _FASTPATH
#include "CSrvrStmt.h"
#include "SrvrCommon.h"
#endif
#include "Debug.h"
#include <sys/types.h>//MFC
#include<sys/stat.h>// MFC

#ifdef __cplusplus
extern "C" {
#endif

namespace interface{
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
        int fetchSize);
}



#ifdef __cplusplus
}
#endif
#endif

