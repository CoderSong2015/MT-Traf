/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <string>
/* Header for class org_apache_trafodion_jdbc_t2_SQLMXConnection */

#ifndef _Included_org_apache_trafodion_jdbc_t2_SQLMXConnection
#define _Included_org_apache_trafodion_jdbc_t2_SQLMXConnection
#ifdef __cplusplus
extern "C" {
#endif
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_UNKNOWN
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_UNKNOWN 0L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_SELECT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_SELECT 1L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_UPDATE
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_UPDATE 2L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_DELETE
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_DELETE 4L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_INSERT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_INSERT 8L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_INSERT_PARAM
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_INSERT_PARAM 288L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_EXPLAIN
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_EXPLAIN 16L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CREATE
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CREATE 32L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_GRANT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_GRANT 64L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_DROP
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_DROP 128L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CALL
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CALL 2048L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CONTROL
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TYPE_CONTROL 2304L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_INS_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_INS_LOB_DATA_STMT 0L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_LOB_DATA_STMT 1L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_LOB_LEN_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_LOB_LEN_STMT 2L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_DEL_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_DEL_LOB_DATA_STMT 3L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_TRUN_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_TRUN_LOB_DATA_STMT 4L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_UPD_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_UPD_LOB_DATA_STMT 5L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_STRT_DATA_LOC_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_CLOB_GET_STRT_DATA_LOC_STMT 6L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_INS_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_INS_LOB_DATA_STMT 7L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_LOB_DATA_STMT 8L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_LOB_LEN_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_LOB_LEN_STMT 9L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_DEL_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_DEL_LOB_DATA_STMT 10L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_TRUN_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_TRUN_LOB_DATA_STMT 11L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_UPD_LOB_DATA_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_UPD_LOB_DATA_STMT 12L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_STRT_DATA_LOC_STMT
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_BLOB_GET_STRT_DATA_LOC_STMT 13L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_READ_UNCOMMITTED
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_READ_UNCOMMITTED 1L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_READ_COMMITTED
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_READ_COMMITTED 2L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_REPEATABLE_READ
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_REPEATABLE_READ 4L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_SERIALIZABLE
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_TXN_SERIALIZABLE 8L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_INVALID
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_INVALID 0L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_INTERNAL
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_INTERNAL 1L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_MIXED
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_MIXED 2L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_EXTERNAL
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_TXN_MODE_EXTERNAL 3L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL 9L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION 10L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG 11L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA 12L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL_FLAG
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_CONTROL_FLAG 8L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG_FLAG
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_CATALOG_FLAG 4L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA_FLAG
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_SCHEMA_FLAG 2L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION_FLAG
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_SQL_SET_TRANSACTION_FLAG 1L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_moduleVersion_
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_moduleVersion_ 12L
#undef org_apache_trafodion_jdbc_t2_SQLMXConnection_moduleTimestamp_
#define org_apache_trafodion_jdbc_t2_SQLMXConnection_moduleTimestamp_ 1234567890LL

long connect(std::string, std::string, std::string);


#ifdef __cplusplus
}
#endif
#endif
