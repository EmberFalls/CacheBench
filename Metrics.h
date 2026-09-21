#ifndef METRICS_H
#define METRICS_H

class Metrics {
private:
    char policyName[32];
    int totalRequests;
    int hits;
    int misses;
    int evictions;

public:
    Metrics();
    void reset(const char *newPolicyName);
    void recordHit();
    void recordMiss();
    void recordEviction();
    int getTotalRequests() const;
    int getHits() const;
    int getMisses() const;
    int getEvictions() const;
    float getHitRatio() const;
    const char *getPolicyName() const;
};

#endif
