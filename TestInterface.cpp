#include "InterfaceDriver.h"
#include "InterfaceConnection.h"
#include "Connection.h"

#include <iostream>

using namespace std;

void TestExecuteDirect();
void TestExecuteDirect2();
int main(){
   // TestExecuteDirect();
    TestExecuteDirect2();

}

void TestExecuteDirect(){
    int rrc = interface::DriverInitialize("utf-8",1,"OFF","");
    //long rc = interface::Connect("hao", "db__root", "123456");
    Connection *cc = new Connection();
    cc->Connect();
    cout << "con" << endl;
    Statement * st = cc->CreateStatement();
    st->ExecuteDirect("create table testtest22(id int)", false, 100, 0);
    int rc = cc->ConnectionClose();

    cout << rc << endl;

}

void TestExecuteDirect2(){
    int rrc = interface::DriverInitialize("utf-8",1,"OFF","");
    //long rc = interface::Connect("hao", "db__root", "123456");
    Connection *cc = new Connection();
    cc->Connect();
    cout << "con" << endl;
    Statement * st = cc->CreateStatement();
    st->ExecuteDirect("insert into testtest22 values(3)", false, 100, 0);
    int rc = cc->ConnectionClose();

    cout << rc << endl;

}

