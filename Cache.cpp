#include "Cache.h"

Cache::Cache(int newCapacity, CachePolicy *newPolicy) {
    capacity = newCapacity;
    if (capacity < 1) capacity = 1;
    if (capacity > MAX_CACHE_SIZE) capacity = MAX_CACHE_SIZE;
    policy = newPolicy;
    reset();
}

void Cache::reset() {
    int i;
    for (i = 0; i < MAX_CACHE_SIZE; i++) entries[i].reset();
    currentTime = 0;
    metrics.reset(policy->getName());
    policy->reset();
}

int Cache::findKey(int key) const {
    int i;
    for (i = 0; i < capacity; i++)
        if (entries[i].isValid() && entries[i].getKey() == key) return i;
    return -1;
}

int Cache::findEmptySlot() const {
    int i;
    for (i = 0; i < capacity; i++) if (!entries[i].isValid()) return i;
    return -1;
}

void Cache::processRequest(int key) {
    int slot;
    currentTime++;
    slot = findKey(key);
    if (slot != -1) {
        entries[slot].markAccess(currentTime);
        metrics.recordHit();
        return;
    }
    metrics.recordMiss();
    slot = findEmptySlot();
    if (slot == -1) {
        slot = policy->chooseVictim(entries, capacity, currentTime);
        metrics.recordEviction();
    }
    entries[slot].insert(key, currentTime);
}

const Metrics &Cache::getMetrics() const { return metrics; }
int Cache::getCapacity() const { return capacity; }
