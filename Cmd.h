#ifndef CMD_H
#define CMD_H
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "BaseCmd.h"

using namespace std;

class Cmd : public BaseCmd {
    private: 
        char** args; //keep arguments
    public:
        Cmd() { };
        Cmd(char ** arg) : args(arg) { }; //constructor with arguments
        int execute() {
            if (args[0] == 0) return 1; //if null command return 0;
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            }
            int procID, status; //for forking and execvp
            procID = fork(); //fork
            
            if(procID == 0) {
                int i = execvp(args[0], args); //run execvp
                exit(i);
            }
            int waitID = wait(&status);
            return status; 
        };
        void addLeft(BaseCmd* l) {}; //do nothing in command
        void addRight(BaseCmd* r) {}; //ditto
        ~Cmd() {
            int argNum = 0; //deallocate arguments, they were all dynamically allocated
            while (args[argNum] != 0) {
                delete[] args[argNum];
                argNum++;
            }
            delete[] args;
            
        };
};
#endif

