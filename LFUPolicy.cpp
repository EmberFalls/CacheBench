#include "LFUPolicy.h"

int LFUPolicy::chooseVictim(CacheEntry entries[], int cacheSize, int currentTime) {
    int victim = -1;
    int i;
    for (i = 0; i < cacheSize; i++) {
        if (entries[i].isValid()) {
            if (victim == -1 ||
                entries[i].getFrequency() < entries[victim].getFrequency() ||
                (entries[i].getFrequency() == entries[victim].getFrequency() &&
                 entries[i].getLastAccessTime() < entries[victim].getLastAccessTime())) {
                victim = i;
            }
        }
    }
    return victim;
}

const char *LFUPolicy::getName() const { return "LFU"; }
