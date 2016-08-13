#ifndef CMDCOMPOSER_H
#define CMDCOMPOSER_H
#include "BaseCmd.h"
#include "Cmd.h"
#include "Connector.h"
#include <sstream>

using namespace std;

class CmdComposer {
    public:
        CmdComposer() { };
        BaseCmd* compose(istringstream &ss) {
            string tstr;
            vector<string> v;
            while (ss >> tstr) {
                v.push_back(tstr);                
            }
            char** args = new char*[v.size() + 1];
            //dynamically allocate mem
            for (int i = 0; i < v.size(); ++i) {
                args[i] = new char[v.at(i).size() + 1];
                strcpy(args[i], v.at(i).c_str());
            }
            args[v.size()] = 0;
            
            return new Cmd(args);
            
        };
};

#endif