#ifndef LFUPOLICY_H
#define LFUPOLICY_H

#include "CachePolicy.h"

class LFUPolicy : public CachePolicy {
public:
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
};

#endif
