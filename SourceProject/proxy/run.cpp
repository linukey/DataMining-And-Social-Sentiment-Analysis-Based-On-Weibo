/*
    author: linukey
    time: 2017.11.12
    ps:
*/

#include "include/webserver.h"
#include <iostream>

using namespace std;
using namespace linukey::webserver;

int main(){
    try{
        WebServer webserver;
        webserver.run();
    } catch (string ex) {
        cerr << ex << endl;
    }
    
    return 0;
}

