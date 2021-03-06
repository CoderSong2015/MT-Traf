#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include <string>
#include "Connection.h"

class Statement{
public:
    Statement();
    Statement(class Connection*);
    long GetDialogueId();
    void ExecuteDirect(std::string sql, bool is_select, int query_timeout, short resultset_holdability);
    std::string GetStmtLabel();
    std::string GetCursorName();
    bool IsSelect();
    int GetQueryTimeout();
    long GetStmtId();
private:
    long dialogue_id_;
    class Connection* conn_;
    int query_timeout_;
    long stmt_id_;      // Pointer to SRVR_STMT_HDL structure in native mode
    std::string cursor_name_;
    std::string stmt_label_;
};


inline
long Statement::GetDialogueId(){
    return this->dialogue_id_;
}

inline
int Statement::GetQueryTimeout(){
    return this->query_timeout_;
}

inline
long Statement::GetStmtId(){
    return this->stmt_id_;
}

inline
std::string Statement::GetCursorName(){
    return "";
}

inline
std::string Statement::GetStmtLabel(){
    return "STMT_TEST";
}
#endif

