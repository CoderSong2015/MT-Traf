#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "Connection.h"
class Statement{
public:
    Statement();
    Statement(class Connection*);
    long GetDialogueId();

private:
    long dialogue_id_;
    class Connection* conn_;

};


inline
long Statement::GetDialogueId(){
    return this->dialogue_id_;
}
#endif

