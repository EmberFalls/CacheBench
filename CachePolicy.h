#ifndef CACHEPOLICY_H
#define CACHEPOLICY_H

#include "CacheEntry.h"

class CachePolicy {
public:
    virtual ~CachePolicy() {}
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime) = 0;
    virtual const char *getName() const = 0;
    virtual void reset() {}
};

#endif
