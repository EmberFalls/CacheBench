#include "BenchmarkEngine.h"
#include "Cache.h"
#include "LRUPolicy.h"
#include "LFUPolicy.h"
#include "SecondChancePolicy.h"
#include "AdaptiveHybridPolicy.h"
#include <iostream.h>
#include <iomanip.h>

BenchmarkEngine::BenchmarkEngine(const Workload &newWorkload, int newCacheCapacity) {
    workload = newWorkload;
    cacheCapacity = newCacheCapacity;
    if (cacheCapacity < 1) cacheCapacity = 1;
    if (cacheCapacity > MAX_CACHE_SIZE) cacheCapacity = MAX_CACHE_SIZE;
    resultCount = 0;
}

Metrics BenchmarkEngine::runPolicy(CachePolicy *policy) {
    Cache cache(cacheCapacity, policy);
    int i;
    for (i = 0; i < workload.getRequestCount(); i++) cache.processRequest(workload.getRequest(i));
    return cache.getMetrics();
}

void BenchmarkEngine::runAll() {
    LRUPolicy lru;
    LFUPolicy lfu;
    SecondChancePolicy secondChance;
    AdaptiveHybridPolicy adaptive;
    resultCount = 0;
    results[resultCount++] = runPolicy(&lru);
    results[resultCount++] = runPolicy(&lfu);
    results[resultCount++] = runPolicy(&secondChance);
    results[resultCount++] = runPolicy(&adaptive);
}

void BenchmarkEngine::runOne(CachePolicy *policy) {
    resultCount = 0;
    results[resultCount++] = runPolicy(policy);
}

void BenchmarkEngine::printHeader() const {
    cout << "\nWorkload: " << workload.getName() << endl;
    cout << "Cache Capacity: " << cacheCapacity << endl;
    cout << "Total Requests: " << workload.getRequestCount() << endl << endl;
    cout << "Policy                 Hits  Misses  Evictions  Hit Ratio" << endl;
    cout << "---------------------------------------------------------" << endl;
}

void BenchmarkEngine::printReport() const {
    int i;
    printHeader();
    for (i = 0; i < resultCount; i++) {
        cout << setw(22) << left << results[i].getPolicyName()
             << setw(6) << right << results[i].getHits()
             << setw(8) << results[i].getMisses()
             << setw(11) << results[i].getEvictions()
             << setw(10) << setprecision(1) << fixed << results[i].getHitRatio() << "%" << endl;
    }
}
