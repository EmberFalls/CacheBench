#ifndef CACHE_H
#define CACHE_H

#include "CacheEntry.h"
#include "CachePolicy.h"
#include "Metrics.h"

#define MAX_CACHE_SIZE 100

class Cache {
private:
    CacheEntry entries[MAX_CACHE_SIZE];
    int capacity;
    int currentTime;
    CachePolicy *policy;
    Metrics metrics;
    int findKey(int key) const;
    int findEmptySlot() const;

public:
    Cache(int newCapacity, CachePolicy *newPolicy);
    void reset();
    void processRequest(int key);
    const Metrics &getMetrics() const;
    int getCapacity() const;
};

#endif
