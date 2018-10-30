
#include "InterfaceConnection.h"
#include <iostream>
using namespace std;
int main(){

    long rc = connect("hao", "db__root", "123456");
    cout << rc << endl;


}
