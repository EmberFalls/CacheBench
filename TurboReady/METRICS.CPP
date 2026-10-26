#include "METRICS.H"
#include <string.h>

Metrics::Metrics() { reset(""); }

void Metrics::reset(const char *newPolicyName) {
    strcpy(policyName, newPolicyName);
    totalRequests = 0;
    hits = 0;
    misses = 0;
    evictions = 0;
}

void Metrics::recordHit() { hits++; totalRequests++; }
void Metrics::recordMiss() { misses++; totalRequests++; }
void Metrics::recordEviction() { evictions++; }
int Metrics::getTotalRequests() const { return totalRequests; }
int Metrics::getHits() const { return hits; }
int Metrics::getMisses() const { return misses; }
int Metrics::getEvictions() const { return evictions; }
float Metrics::getHitRatio() const {
    if (totalRequests == 0) return 0.0;
    return ((float)hits * 100.0) / (float)totalRequests;
}
const char *Metrics::getPolicyName() const { return policyName; }
