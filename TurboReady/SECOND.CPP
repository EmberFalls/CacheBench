#include "SECOND.H"

SecondChancePolicy::SecondChancePolicy() { reset(); }

void SecondChancePolicy::reset() { clockPointer = 0; }

int SecondChancePolicy::chooseVictim(CacheEntry entries[], int cacheSize, int currentTime) {
    int checked = 0;
    int victim;
    while (checked < cacheSize * 2) {
        if (entries[clockPointer].getReferenceBit() == 0) {
            victim = clockPointer;
            clockPointer = (clockPointer + 1) % cacheSize;
            return victim;
        }
        entries[clockPointer].clearReferenceBit();
        clockPointer = (clockPointer + 1) % cacheSize;
        checked++;
    }
    victim = clockPointer;
    clockPointer = (clockPointer + 1) % cacheSize;
    return victim;
}

const char *SecondChancePolicy::getName() const { return "Second-Chance"; }
