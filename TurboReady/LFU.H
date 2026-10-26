#ifndef LFU_H
#define LFU_H

#include "POLICY.H"

class LFUPolicy : public CachePolicy {
public:
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
};

#endif
