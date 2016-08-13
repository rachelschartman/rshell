#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "BaseCmd.h"
    
class Connector : public BaseCmd {
    private:
        BaseCmd* left;
        BaseCmd* right;
        string type;
    public:
        Connector() { };
        Connector(BaseCmd* l, BaseCmd* r, string t) : left(l), right(r), 
            type(t) { };
        int execute() {
            //insert stuff here 
        };
};
#endif