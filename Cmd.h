#ifndef CMD_H
#define CMD_H
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include "BaseCmd.h"

using namespace std;

class Cmd : public BaseCmd {
    private: 
        char** args;
    public:
        Cmd() { };
        Cmd(char ** arg) : args(arg) { };
        int execute() {
            int procID, status;
            procID = fork();
            
            if(procID == 0) {
                int i = execvp(args[0], args);
                exit(i);
            }
            int waitID = wait(&status);
            return status;
        };
};
#endif
