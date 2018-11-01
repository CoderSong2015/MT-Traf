#include "Connection.h"

Connection::Connection(){
}

void Connection::Connect(){
    this->dialogue =interface::Connect("hao", "db__root", "123456");
}

long Connection::GetDialogueID(){
    return this->dialogue;
}

int Connection::ConnectionClose(){
    interface::ConnectionClose("hao", this->GetDialogueID());
    return 0;
}

