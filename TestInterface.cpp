#include "SQLMXDriver.h"
#include "InterfaceConnection.h"

#include <iostream>

using namespace std;
int main(){
    int rrc = DriverInitialize("utf-8",1,"OFF","");
    long rc = Connect("hao", "db__root", "123456");
    cout << "con" << endl;
    rc = ConnectionClose("hao", rc);
    cout << rc << endl;
    while(1);

}
