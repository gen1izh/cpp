#ifndef I_TOP_MANAGER_H
#define I_TOP_MANAGER_H

class ITopManager {

public:
    ITopManager() {}

    virtual ~ITopManager(){}

    virtual int load() = 0;

    virtual int finalize() = 0;

};

#endif // I_TOP_MANAGER_H

