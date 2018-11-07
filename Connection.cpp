#include "Connection.h"

Connection::Connection():dialogue_id_(0),
                         auto_commit_(true),
                         tx_id_(0),
                         transaction_isolation_(1),
                         catalog_("trafodion"),
                         schema_("seabase"),
                         is_connection_init_(false),
                         is_connection_closed_(true){
}

Connection::~Connection(){
    if(!this->is_connection_closed_){
        ConnectionClose();
    }
}

void Connection::Connect(){
    if (is_connection_closed_){
        this->dialogue_id_ =interface::Connect("hao", "db__root", "123456");
        this->is_connection_closed_ = false;
    }
    else{
    }
}

int Connection::ConnectionClose(){
    int rc = interface::ConnectionClose("hao", GetDialogueId());

    if(0 == rc){
        this->is_connection_closed_ = true;
    }
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

    if(GetIsInit()){
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
        this->is_connection_init_ = false;
    }
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
