#ifndef __INTERFACESTATEMENT_H_
#define __INTERFACESTATEMENT_H_
#include <platform_ndcs.h>
#ifdef NSK_PLATFORM
        #include <sqlWin.h>
        #include <windows.h>
#else
        #include <sql.h>
#endif
#include <sqlext.h>
#include "JdbcDriverGlobal.h"
#include "CoreCommon.h"
#include "InterfaceCommonFunctions.h"
#include "CSrvrConnect.h"
#include "Debug.h"

#ifdef __cplusplus
extern "C" {
#endif

void ExecuteDirect(string, long, int, bool, int, string, string, string, bool, int, int, long);

#ifdef __cplusplus
}
#endif
#endif


