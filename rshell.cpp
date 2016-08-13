#include <iostream>
#include "BaseCmd.h"
#include "CmdComposer.h"
#include <sstream>
#include <unistd.h>

using namespace std;


int main() {
    CmdComposer composer;
    char user[40];
    char host[40];
    

    //main loop
    while (true) {
        cout << "$ ";
        string str;
        getline(cin, str);
        istringstream ss(str);
        BaseCmd* bc = composer.compose(ss);
        bc->execute();
    }
}