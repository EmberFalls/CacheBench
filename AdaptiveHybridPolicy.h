#ifndef ADAPTIVEHYBRIDPOLICY_H
#define ADAPTIVEHYBRIDPOLICY_H

#include "CachePolicy.h"

class AdaptiveHybridPolicy : public CachePolicy {
private:
    int frequencyWeight;
    int recencyWeight;
    int retentionScore(CacheEntry &entry, int currentTime) const;

public:
    AdaptiveHybridPolicy(int newFrequencyWeight = 60, int newRecencyWeight = 40);
    virtual int chooseVictim(CacheEntry entries[], int cacheSize, int currentTime);
    virtual const char *getName() const;
    void setWeights(int newFrequencyWeight, int newRecencyWeight);
};

#endif
