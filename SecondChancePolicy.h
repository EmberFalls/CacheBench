#ifndef SECONDCHANCEPOLICY_H
#define SECONDCHANCEPOLICY_H

#include "CachePolicy.h"

class SecondChancePolicy : public CachePolicy {
private:
    int clockPointer;

public:
    SecondChancePolicy();
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
    virtual void reset();
};

#endif
