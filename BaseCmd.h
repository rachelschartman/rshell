#ifndef BASECMD_H
#define BASECMD_H
#include <iostream>
using namespace std;

class BaseCmd {
  public:
    BaseCmd() { };
    virtual int execute() = 0; //function that allows execution
    virtual void addLeft(BaseCmd* l) = 0; //for the connectors
    virtual void addRight(BaseCmd* r) = 0; //for connectors
    virtual ~BaseCmd() {}; //virtual destructor to deal with dynamic memory, all
                           //commands are allocated in dynamic memory
};
#endif
