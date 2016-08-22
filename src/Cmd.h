#ifndef CMD_H
#define CMD_H
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
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
            else if ((strcmp(args[0], "test") == 0) || strcmp(args[0], "[") == 0) { //test command
                int option = 0; //default to -e (0 for e, 1 for f, 2 for d)
                int index = 1; //default index for file path
                
                if (strcmp(args[1], "-e") == 0) {
                    index++; //
                }
                else if (strcmp(args[1], "-f") == 0) {
                    index++;
                    option = 1;
                }
                else if (strcmp(args[1], "-d") == 0) {
                    index++;
                    option = 2;
                }
                struct stat info; 
                if ( stat( args[index], &info ) != 0) { //if file doesn't exist
                    cout << "(False)" << endl;
                    return 1;
                }
                else if ( info.st_mode & S_IFDIR ) { //if it's a directory
                    if (option == 0 || option == 2) {
                        cout << "(True)" << endl;
                        return 0;
                    }
                    else { 
                        cout << "(False)" << endl; 
                        return 1;
                    }
                }
                else { //if it's a file
                    if (option == 1 || option == 0) {
                        cout << "(True)" << endl;
                        return 0;
                    } else {
                        cout << "(False)" << endl;
                        return 1;
                    }
                }
                return 0;
            }
            int procID, status; //for forking and execvp
            procID = fork(); //fork
            
            if(procID == 0) {
                int i = execvp(args[0], args); //run execvp
                exit(i);
            }
            wait(&status);
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

