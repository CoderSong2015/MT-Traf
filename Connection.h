#include "InterfaceConnection.h"

class Connection{

public:
    Connection();
    void Connect();
    long GetDialogueID();
    int ConnectionClose();
private:
    long dialogue;
};
