#ifndef BENCH_H
#define BENCH_H

#include "WORKLOAD.H"
#include "METRICS.H"
#include "POLICY.H"

class BenchmarkEngine {
private:
    Workload workload;
    int cacheCapacity;
    Metrics results[4];
    int resultCount;
    Metrics runPolicy(CachePolicy *policy);
    void printHeader() const;

public:
    BenchmarkEngine(const Workload &newWorkload, int newCacheCapacity);
    void runAll();
    void runOne(CachePolicy *policy);
    void printReport() const;
};

#endif
