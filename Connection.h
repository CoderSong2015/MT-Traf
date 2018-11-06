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
    void CreateStatement();
    class Statement* GetStatement();
    void SetAutoCommit(bool AutoCommit);
    bool GetAutoCommit();
    std::string GetServer();
    int GetTransactionMode();
private:
    long dialogue_id_;
    std::string server_;
    bool auto_commit_;
    class Statement* stmt_;
    int tx_id_;
    int transaction_mode_;
};

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

#endif
