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

bool getSqlStmtType(unsigned char* sql){
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

/*
void setFetchOutputs(JNIEnv *jenv, jobject jobj, SRVR_STMT_HDL *pSrvrStmt,
                SQLValueList_def  *outputValueList,
                long rowsAffected, BOOL endOfData,
                BOOL doCallBack, jint txid)
        {
                FUNCTION_ENTRY_LEVEL(DEBUG_LEVEL_STMT,"setFetchOutputs",("pSrvrStmt=0x%08x, outputValueList=0x%08x, rowsAffected=%ld, endOfData=%d, doCallBack=%d, txid=0x%08x",
                        pSrvrStmt,
                        outputValueList,
                        rowsAffected,
                        endOfData,
                        doCallBack,
                        txid));

                jobjectArray    rowArray;

                long                    columnCount;
                long                    rowIndex;
                long                    columnIndex;
                SQLValue_def    *SQLValue;

                rowArray = JNI_NewObjectArray(jenv,rowsAffected, gJNICache.wrapperClass, NULL);
                if (rowsAffected != 0) columnCount = outputValueList->_length / rowsAffected;
                else columnCount = 0;

                DEBUG_OUT(DEBUG_LEVEL_STMT,("columnCount=%ld, rowsAffected=%ld",columnCount,rowsAffected));

                for (rowIndex = 0; rowIndex < rowsAffected ; rowIndex++)
                {
                        struct WrapperInfoStruct wrapperInfo;

                        if (!createWrapper(&wrapperInfo,jenv,columnCount,true))
                        {
                                //throwSQLException(jenv, JVM_MEM_ALLOC_ERROR, NULL, "HY000");
                                cleanupWrapperInfo(&wrapperInfo);
                                FUNCTION_RETURN_PTR(NULL,("setFetchOutputs - JVM_MEM_ALLOC_ERROR"));
                        }

                        for (columnIndex = 0 ; columnIndex < columnCount ; columnIndex++)
                        {
                                SQLValue = (SQLValue_def *)outputValueList->_buffer +
                                        (rowIndex * columnCount) + columnIndex;

                                if (SQLValue->dataInd != -1)
                                {
                                        if (!setWrapper(&wrapperInfo, jobj, pSrvrStmt, columnIndex, SQLValue))
                                        {
                                                cleanupWrapperInfo(&wrapperInfo);
                                                FUNCTION_RETURN_PTR(NULL,("setWrapper returned error"));
                                        }
                                        DEBUG_OUT(DEBUG_LEVEL_DATA,("Column index %ld wrapper is 0x%08x",
                                                columnIndex, wrapperInfo.wrapper));
                                }
                        }
                        updateWrapperElements(&wrapperInfo);

                        JNI_SetObjectArrayElement(jenv,rowArray, rowIndex, wrapperInfo.wrapper);

                        cleanupWrapperInfo(&wrapperInfo);
                }

                 // If requested, do the callback to Java.
                // If not, they just wanted the Row[] created.
                if(doCallBack)
                {
                        jenv->CallVoidMethod(jobj, gJNICache.fetchOutputsMethodId, rowArray,
                                rowsAffected, endOfData, txid);
                }
                FUNCTION_RETURN_PTR(rowArray, (NULL));
        }
*/
/*
void setExecuteDirectOutputs(SQLItemDescList_def *outputDesc,
                long rowsAffected, jint txid, jlong stmtId)
        {
                FUNCTION_ENTRY_LEVEL(DEBUG_LEVEL_STMT,"setExecuteDirectOutputs",("jenv=0x%08x, jobj==0x%08x, outputDesc=0x%08x, rowsAffected=%ld, txid=0x%08x, stmtId=0x%08x",
                        jenv,
                        jobj,
                        outputDesc,
                        rowsAffected,
                        txid,
                        stmtId));
                jobjectArray            SQLMXOuputDescArray = NULL;

                SQLMXOuputDescArray = NewDescArray(jenv, jobj, outputDesc, 0);
                char *         fetchedRows = NULL;
                int            fetchedRowCount = 0;

                int            stmtType = INVALID_SQL_QUERY_STMT_TYPE; // Initialize to invalid type

                SRVR_STMT_HDL *pSrvrStmt = (SRVR_STMT_HDL *) stmtId;

                if (pSrvrStmt != NULL)
                {
                        {
                                stmtType = pSrvrStmt->getSqlQueryStatementType();
                                DEBUG_OUT(DEBUG_LEVEL_CLI|DEBUG_LEVEL_STMT,("SQL Query Statement Type=%s",
                                        CliDebugSqlQueryStatementType(stmtType)));

                                if(stmtType == SQL_SELECT_UNIQUE)
                                {
                                        // For unique selects, the endOfData flag indicates if
                                        //   the select returned a row or not
                                        if(pSrvrStmt->endOfData) fetchedRowCount = 0;
                                        else fetchedRowCount = 1;

                                        // Go get the Row[] object to return to the Java layer
                                        fetchedRows = setFetchOutputs(jenv, pSrvrStmt->resultSetObject, pSrvrStmt,
                                                &pSrvrStmt->outputValueList, fetchedRowCount,
                                                TRUE, FALSE, txid);
                                }
                        }
                }
                // Return the execute results and any result set
                //   information that may have been generated
                jenv->CallVoidMethod(jobj, gJNICache.execDirectOutputsMethodId, SQLMXOuputDescArray, rowsAffected,
                        fetchedRows, fetchedRowCount, txid, stmtId, stmtType);

                FUNCTION_RETURN_VOID((NULL));
}
*/
