#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>
#include "InterfaceConnection.h"
#include "Statement.h"

class Connection{

public:
    Connection();
    void Connect();
    int ConnectionClose();
    long GetDialogueId();
    int GetTxId();
    class Statement* CreateStatement();
    class Statement* GetStatement();
    void SetAutoCommit(bool AutoCommit);
    bool GetAutoCommit();
    std::string GetServer();
    int GetTransactionMode();
    void ConnectionInit();

    std::string GetCatalog();
    std::string GetSchema();
    std::string GetMploc();
    bool GetIsReadOnly();
    int GetTransactionIsolation();
    int GetLoginTimeout();
    int GetQueryTimeout();
    std::string GetModulecaching();
    std::string GetCompiledmodulelocation();
    bool GetblnDoomUsrTxn();
    int GetStatisticsIntervalTime();
    int GetStatisticsLimitTime();
    std::string GetStatisticsType();
    std::string GetProgramStatisticsEnabled();
    std::string GetStatisticsSqlPlanEnabled();
    int MapTxnIsolation(int);
    bool GetIsInit();
private:
    long dialogue_id_;
    std::string server_;
    bool auto_commit_;
    class Statement* stmt_;
    int tx_id_;
    int transaction_mode_;
    std::string catalog_;
    std::string schema_;
    std::string mploc_;
    bool is_read_only_;
    int transaction_isolation_;
    int login_timeout_;
    int query_timeout_;
    std::string modulecaching_;
    std::string compiled_module_location_;
    bool bln_doom_usr_txn_;
    int statistics_interval_time_;
    int statistics_limit_time_;
    std::string statistics_type_;
    std::string program_statistics_enabled_;
    std::string statistics_sql_plan_enabled_;
    bool is_connection_init;
};

inline
bool Connection::GetIsInit(){
    return this->is_connection_init;
}

inline
long Connection::GetDialogueId(){
    return this->dialogue_id_;
}

inline
bool Connection::GetAutoCommit(){
    return this->auto_commit_;
}

inline
void Connection::SetAutoCommit(bool auto_commmit){
    this->auto_commit_ = auto_commmit;
}

inline
std::string Connection::GetServer(){
    return this->server_;
}

inline
int Connection::GetTxId(){
    return this->tx_id_;
}

inline
int Connection::GetTransactionMode(){
    return this->transaction_mode_;
}

inline
std::string Connection::GetCatalog(){
    return this->catalog_;
}

inline
std::string Connection::GetSchema(){
    return this->schema_;
}

inline
std::string Connection::GetMploc(){
    return this->mploc_;
}

inline
bool Connection::GetIsReadOnly(){
    return this->is_read_only_;
}

inline
int Connection::GetTransactionIsolation(){
    return this->transaction_isolation_;
}

inline
int Connection::GetLoginTimeout(){
    return this->login_timeout_;
}

inline
int Connection::GetQueryTimeout(){
    return this->query_timeout_;
}

inline
std::string Connection::GetModulecaching(){
    return this->modulecaching_;
}

inline
std::string Connection::GetCompiledmodulelocation(){
    return this->compiled_module_location_;
}

inline
bool Connection::GetblnDoomUsrTxn(){
    return this->bln_doom_usr_txn_;
}

inline
int Connection::GetStatisticsIntervalTime(){
    return this->statistics_interval_time_;
}

inline
int Connection::GetStatisticsLimitTime(){
    return this->statistics_limit_time_;
}

inline
std::string Connection::GetStatisticsType(){
    return this->statistics_type_;
}

inline
std::string Connection::GetProgramStatisticsEnabled(){
    return this->program_statistics_enabled_;
}

inline
std::string Connection::GetStatisticsSqlPlanEnabled(){
    return this->statistics_sql_plan_enabled_;
}



#endif
