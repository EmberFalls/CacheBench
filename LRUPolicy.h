#ifndef LRUPOLICY_H
#define LRUPOLICY_H

#include "CachePolicy.h"

class LRUPolicy : public CachePolicy {
public:
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
};

#endif
