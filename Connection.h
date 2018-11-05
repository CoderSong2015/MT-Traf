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
    long GetDialogueID();
    void CreateStatement();
    Statement* GetStatement();
    void SetAutoCommit(bool AutoCommit);
    bool GetAutoCommit();

private:
    long dialogue_id_;
    std::string server_;
    bool auto_commit_;
    class Statement* stmt_;

};

inline
long Connection::GetDialogueID(){
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

#endif
