#include "InterfaceStatement.h"
#include "Statement.h"

Statement::Statement(Connection* conn):conn_(conn){
}

void Statement::ExecuteDirect(std::string sql, bool is_select, int query_timeout, short resultset_holdability){

    interface::ExecuteDirect(conn_->GetServer(),
                             conn_->GetDialogueId(),
                             conn_->GetTxId(),
                             conn_->GetAutoCommit(),
                             conn_->GetTransactionMode(),
                             GetStmtLabel(),
                             GetCursorName(),
                             sql.c_str(),
                             is_select,
                             query_timeout,
                             resultset_holdability,
                             GetStmtId());

}
