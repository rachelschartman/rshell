#include <iostream>
#include "BaseCmd.h"
#include "CmdComposer.h"
#include <sstream>
#include <unistd.h>

using namespace std;


int main() {
    CmdComposer composer;
    char u[40]; //extra credit :-)
    char h[40];
    for (int i = 0; i < 40; ++i) {
        u[i] = 0;
        h[i] = 0;
    }
    gethostname(h, 40);
    getlogin_r(u, 40);

    //main loop
    while (true) { // main loop
        cout << u << "@" << h << "$ "; //print prompt
        string str;
        getline(cin, str); //get line of command
        istringstream ss(str); //set up strin stream
        BaseCmd* bc = composer.compose(ss); //compose command into tree
        bc->execute(); //execute command
        delete bc; //deallocate memory-- no memory leaks allowed
    }
}