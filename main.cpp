#include "Cmd.h"

int main() {
    
    char** args = new char*[3];
    args[0] = "ls";
    args[1] = "-a";
    args[2] = 0;
    
    Cmd cmd(args);
    cmd.execute();
    return 0;
}