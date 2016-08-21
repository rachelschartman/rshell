#ifndef PARENCMD_H
#define PARENCMD_H
#include "BaseCmd.h"

class ParenCmd : public BaseCmd {
    private:
        BaseCmd* c;
    public:
        ParenCmd() { };
        ParenCmd(BaseCmd* cmd) : c(cmd) { }; 
        int execute() {
            return c->execute();     
        };
        void addRight(BaseCmd* r) {
            
        };
        void addLeft(BaseCmd* l) {
            
        };
};

#endif