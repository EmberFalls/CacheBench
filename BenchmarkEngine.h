#ifndef BENCHMARKENGINE_H
#define BENCHMARKENGINE_H

#include "Workload.h"
#include "Metrics.h"
#include "CachePolicy.h"

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
