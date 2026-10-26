#include "LRU.H"

int LRUPolicy::chooseVictim(CacheEntry entries[], int cacheSize, int currentTime) {
    int victim = -1;
    int oldestTime = 0;
    int i;
    for (i = 0; i < cacheSize; i++) {
        if (entries[i].isValid()) {
            if (victim == -1 || entries[i].getLastAccessTime() < oldestTime) {
                victim = i;
                oldestTime = entries[i].getLastAccessTime();
            }
        }
    }
    return victim;
}

const char *LRUPolicy::getName() const { return "LRU"; }
