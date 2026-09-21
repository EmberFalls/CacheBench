#include "AdaptiveHybridPolicy.h"

AdaptiveHybridPolicy::AdaptiveHybridPolicy(int newFrequencyWeight, int newRecencyWeight) {
    setWeights(newFrequencyWeight, newRecencyWeight);
}

void AdaptiveHybridPolicy::setWeights(int newFrequencyWeight, int newRecencyWeight) {
    frequencyWeight = newFrequencyWeight;
    recencyWeight = newRecencyWeight;
}

int AdaptiveHybridPolicy::retentionScore(CacheEntry &entry, int currentTime) const {
    int frequencyScore = entry.getFrequency() * 10;
    int age = currentTime - entry.getLastAccessTime();
    int recencyScore;
    if (frequencyScore > 100) frequencyScore = 100;
    if (age > 100) age = 100;
    if (age < 0) age = 0;
    recencyScore = 100 - age;
    return frequencyWeight * frequencyScore + recencyWeight * recencyScore;
}

int AdaptiveHybridPolicy::chooseVictim(CacheEntry entries[], int cacheSize, int currentTime) {
    int victim = -1;
    int lowestScore = 0;
    int score;
    int i;
    for (i = 0; i < cacheSize; i++) {
        if (entries[i].isValid()) {
            score = retentionScore(entries[i], currentTime);
            if (victim == -1 || score < lowestScore ||
                (score == lowestScore &&
                 entries[i].getLastAccessTime() < entries[victim].getLastAccessTime())) {
                victim = i;
                lowestScore = score;
            }
        }
    }
    return victim;
}

const char *AdaptiveHybridPolicy::getName() const { return "Adaptive Hybrid"; }
