#ifndef BASECMD_H
#define BASECMD_H

class BaseCmd {
  public:
    BaseCmd() { };
    virtual int execute() = 0;
};
#endif
