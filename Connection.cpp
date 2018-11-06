#include "Connection.h"

Connection::Connection(){
}

void Connection::Connect(){
    this->dialogue_id_ =interface::Connect("hao", "db__root", "123456");
}

int Connection::ConnectionClose(){
    interface::ConnectionClose("hao", this->GetDialogueId());
    return 0;
}

void Connection::CreateStatement(){
    //ConnectionInit()?
    this->stmt_ = new Statement(this);
}

Statement* Connection::GetStatement(){
    //ConnectionInit()?
    return this->stmt_;
}


