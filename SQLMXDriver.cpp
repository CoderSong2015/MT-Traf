/**************************************************************************
// @@@ START COPYRIGHT @@@
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// @@@ END COPYRIGHT @@@
**************************************************************************/
//
// MODULE: SQLMXDriver.cpp
//
/**************************************************************************/
/*
  * Methods Changed: Java_org_apache_trafodion_jdbc_t2_T2Driver_SQLMXInitialize(JNIEnv *, jclass, jstring, jint, jstring, jstring)
  */
#include <platform_ndcs.h>
#include <sys/types.h> /* optional except for POSIX.1 */
#include <unistd.h>
#ifdef NSK_PLATFORM
#include <sqlWin.h>
#include <windows.h>
#include "cextdecs.h"
#include "NskUtil.h"
#include "pThreadsSync.h"
#else
#include <sql.h>
#endif
/*
#include "Vproc.h"

#include "CoreCommon.h"

#include "JdbcDriverGlobal.h"
#include "SQLMXCommonFunctions.h"

#include "Debug.h"

#include "CommonLogger.h"
#include "sqlcli.h"
*/
#include "SQLMXDriver.h"
#include <sqlext.h>
#include "GlobalInformation.h"
#include "SrvrCommon.h"
static bool driverVersionChecked = false;
#ifdef NSK_PLATFORM	// Linux port - ToDo txn related
int client_initialization(void);
#endif

void setTM_enable_cleanup ()
{
  static bool sv_envvar_setup = false;
  if (sv_envvar_setup) {
    return;
  }
  putenv("TMLIB_ENABLE_CLEANUP=0");
  sv_envvar_setup = true;
}

/*
* Class:     org_apache_trafodion_jdbc_t2_T2Driver
* Method:    SQLMXInitialize
* Signature: (Ljava/lang/String;I)V
*/
// MFC - added two parameters to set the MFC on/off and the directory

int DriverInitialize(std::string language, int nowaitOn, std::string moduleCaching, std::string compiledModuleLocation)
{

	const char 					*nLanguage;
	//	static GlobalInformation	*globalInfo = new GlobalInformation();
	//MFC
	const char					*nModuleCaching;
	const char					*nCompiledModuleLocation;


	GlobalInformation::setSQLMX_Version();

	if (srvrGlobal == NULL)
		MEMORY_ALLOC_PERM(srvrGlobal,SRVR_GLOBAL_Def)
	else
	{
		if (srvrGlobal->boolFlgforInitialization == 1)
			FUNCTION_RETURN_NUMERIC(0, ("Already Initialized"));
	}

#ifdef NSK_PLATFORM		// Linux port
	if (language)
	{
		nLanguage = JNI_GetStringUTFChars(jenv,language, NULL);
		if (strcmp(nLanguage, "ja") == 0)
		{
			srvrGlobal->clientLCID = MAKELCID(MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT), SORT_DEFAULT);
			srvrGlobal->clientErrorLCID = srvrGlobal->clientLCID;
		}
		else
			if (strcmp(nLanguage, "en") == 0)
			{
				srvrGlobal->clientLCID = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), SORT_DEFAULT);
				srvrGlobal->clientErrorLCID = srvrGlobal->clientLCID;
			}
			else
			{
				srvrGlobal->clientLCID = LANG_NEUTRAL;
				srvrGlobal->clientErrorLCID = LANG_NEUTRAL;
			}
			JNI_ReleaseStringUTFChars(jenv,language, nLanguage);
	}
	else
	{
		srvrGlobal->clientLCID = LANG_NEUTRAL;
		srvrGlobal->clientErrorLCID = LANG_NEUTRAL;
	}
#endif

	srvrGlobal->dialogueId = 0;			// DialogueId is set to zero now

	// Linux port - Nowait support is set to OFF for now.
	// nowaitOn = 0;	// Should come command line or JDBC properties

	switch (nowaitOn)
	{
	case 0:
		srvrGlobal->nowaitOn = 0;
		break;
	case 1:
		srvrGlobal->nowaitOn = 1;
		break;
	case 2:
		srvrGlobal->nowaitOn = 2;
		break;
	default:
		srvrGlobal->nowaitOn = 0;
		break;
	}

#ifdef NSK_PLATFORM		// Linux port
	// setup MP system catalog name
	if (envGetSystemCatalogName (&srvrGlobal->NskSystemCatalogName[0]) != TRUE)
	{
		throwSQLException(jenv, SYSTEM_CATALOG_ERROR, NULL, "HY000", 0);
		FUNCTION_RETURN_VOID(("envGetSystemCatalogName() failed"));
	}

	// setup MX system catalog name
	if (envGetMXSystemCatalogName (&srvrGlobal->SystemCatalog[0]) != TRUE)
	{
		throwSQLException(jenv, SYSTEM_CATALOG_ERROR, NULL, "HY000", 0);
		FUNCTION_RETURN_VOID(("envGetMXSystemCatalogName() failed"));
	}
#endif

	// MFC - set the srvrGlobal variables w.r.t the properties - start

	srvrGlobal->moduleCaching=0;

    if (moduleCaching == "ON")
        srvrGlobal->moduleCaching=1;

	if (srvrGlobal->moduleCaching == 1)
	{
		memset(srvrGlobal->CurrentCatalog, '\0', 129);
		memset(srvrGlobal->CurrentSchema, '\0', 129);
		memset(srvrGlobal->compiledModuleLocation, '\0', 100);
		if (compiledModuleLocation.empty())
		{
			strcpy(srvrGlobal->compiledModuleLocation,"/usr/tandem/sqlmx/USERMODULES");
		}
		else
		{
			nCompiledModuleLocation = compiledModuleLocation.c_str();
			strcpy(srvrGlobal->compiledModuleLocation,nCompiledModuleLocation);

			if(srvrGlobal->compiledModuleLocation[0] != '/')
			{
				printf("The directory provided for option \"compiledmodulelocation\" must be an absolute path.\n");
				abort();
			}
			int nDirExists = access(srvrGlobal->compiledModuleLocation, F_OK);
			if(nDirExists != 0)
			{
				printf("The directory provided for option \"compiledmodulelocation\" does not exist.\n");
				abort();
			}
			nDirExists = access(srvrGlobal->compiledModuleLocation, W_OK);
			if(nDirExists != 0)
			{
				printf("The directory provided for option \"compiledmodulelocation\" does not have \"write\" permission.\n");
				abort();
			}
			if(srvrGlobal->compiledModuleLocation[strlen(srvrGlobal->compiledModuleLocation)-1] == '/')
			{
				srvrGlobal->compiledModuleLocation[strlen(srvrGlobal->compiledModuleLocation)-1] = '\0';
			}
		}
	}
	srvrGlobal->boolFlgforInitialization = 1;
	// MFC set the srvrGlobal variables w.r.t the properties - end
	FUNCTION_RETURN_NUMERIC(0, "success");
}


/*
* Class:     org_apache_trafodion_jdbc_t2_T2Driver
* Method:    setDefaultEncoding
* Signature: (Ljava/lang/String;)V
*/
void SetDefaultEncoding(string encoding)
{
	//TODO
}



