#include "Connection.h"

Connection::Connection():dialogue_id_(0),
                         auto_commit_(true),
                         tx_id_(0),
                         transaction_isolation_(1),
                         catalog_("trafodion"),
                         schema_("seabase"){
}

void Connection::Connect(){
    dialogue_id_ =interface::Connect("hao", "db__root", "123456");
}

int Connection::ConnectionClose(){
    interface::ConnectionClose("hao", GetDialogueId());
    return 0;
}

Statement* Connection::CreateStatement(){
    //ConnectionInit()?
    ConnectionInit();
    this->stmt_ = new Statement(this);
    return this->stmt_;
}

Statement* Connection::GetStatement(){
    //ConnectionInit()?
    return this->stmt_;
}

void Connection::ConnectionInit(){
    //need to add mutex?
    interface::ConnectionInit(GetServer(),
                              GetDialogueId(),
                              GetCatalog(),
                              GetSchema(),
                              GetMploc(),
                              GetIsReadOnly(),
                              GetAutoCommit(),
                              MapTxnIsolation(GetTransactionIsolation()),
                              GetLoginTimeout(),
                              GetQueryTimeout(),
                              GetModulecaching(),
                              GetCompiledmodulelocation(),
                              GetblnDoomUsrTxn(),
                              GetStatisticsIntervalTime(),
                              GetStatisticsLimitTime(),
                              GetStatisticsType(),
                              GetProgramStatisticsEnabled(),
                              GetStatisticsSqlPlanEnabled()
                              );

}


int Connection::MapTxnIsolation(int level)
{
    int isolationLevel;

    switch (level)
    {
    case 0: // May be we default to SQL/MX default
        isolationLevel = SQL_TXN_READ_COMMITTED;
        break;
    case 1:
        isolationLevel = SQL_TXN_READ_COMMITTED;
        break;
    case 2:
        isolationLevel = SQL_TXN_READ_UNCOMMITTED;
        break;
    case 3:
        isolationLevel = SQL_TXN_REPEATABLE_READ;
        break;
    case 4:
        isolationLevel = SQL_TXN_SERIALIZABLE;
        break;
    default:
        isolationLevel = SQL_TXN_READ_COMMITTED;
        break;
    }
    return isolationLevel;
}
