#ifndef LRU_H
#define LRU_H

#include "POLICY.H"

class LRUPolicy : public CachePolicy {
public:
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
};

#endif
