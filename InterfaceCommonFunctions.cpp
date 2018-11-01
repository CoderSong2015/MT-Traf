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
// MODULE: SQLMXCommonFunctions.cpp
//

#include <string>
#include <platform_ndcs.h>
#include <stdlib.h>
#include <wchar.h>
#include <errno.h>
#include <time.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "sqlcli.h"
#include "JdbcDriverGlobal.h"
//#include "org_apache_trafodion_jdbc_t2_SQLMXConnection.h"
//#include "org_apache_trafodion_jdbc_t2_DataWrapper.h"
#include "InterfaceCommonFunctions.h"
#include "CoreCommon.h"
#include "SrvrCommon.h"
#include "SrvrOthers.h"
#include "Debug.h"
#include "GlobalInformation.h"
//#include "org_apache_trafodion_jdbc_t2_T2Driver.h"  //spjrs

	bool getSqlStmtType(unsigned char* sql)
	{
		char *p = new char[strlen((const char *)sql)+1];
		memset(p, '\0', strlen((const char *)sql)+1);
		strncpy(p, (const char *)sql, strlen((const char *)sql)+1);
		/*
		jstring jstrSQL = gJEnv->NewStringUTF(p);
		jboolean result = gJEnv->CallStaticBooleanMethod(gJNICache.SQLMXConnectionClass, gJNICache.getSqlStmtTypeMethodId, jstrSQL);
		*/
		bool result;
		std::string s = p;
		int x = (s.find_first_of("INSERT") || s.find_first_of("UPDATE") || s.find_first_of("DELETE"));
		int y = (s.find_first_of("insert") || s.find_first_of("update") || s.find_first_of("delete"));
		if(x == 0 || y == 0)
		{
			result = JNI_TRUE;
		}
		else
		{
			result = JNI_FALSE;
		}
		delete [] p;
		p = NULL;
		return result;

	}
