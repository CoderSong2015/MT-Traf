#include "Connection.h"

Connection::Connection():auto_commit_(true){
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
                              GetTransactionIsolation(),
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

