#include "Workload.h"
#include <string.h>

Workload::Workload() { begin("EMPTY"); }

void Workload::begin(const char *newName) {
    requestCount = 0;
    strcpy(name, newName);
}

void Workload::addRequest(int key) {
    if (requestCount < MAX_WORKLOAD_SIZE) requests[requestCount++] = key;
}

void Workload::createRepeated() {
    int pattern[] = {1, 2, 3, 1, 2, 1, 3, 2, 1, 4};
    int i, cycle;
    begin("REPEATED / HOT-SET");
    for (cycle = 0; cycle < 10; cycle++)
        for (i = 0; i < 10; i++) addRequest(pattern[i]);
}

void Workload::createChanging() {
    int i;
    begin("CHANGING / SCAN-HEAVY");
    for (i = 1; i <= 100; i++) addRequest(i);
}

void Workload::createMixed() {
    int i;
    begin("MIXED");
    for (i = 1; i <= 100; i++) {
        addRequest(1); addRequest(2); addRequest(3);
        if (i % 3 == 0) addRequest(100 + i);
        if (i % 5 == 0) addRequest(4);
    }
}

void Workload::createBurst() {
    int period, i, base;
    begin("BURST");
    for (period = 0; period < 4; period++) {
        base = period * 10 + 1;
        for (i = 0; i < 25; i++) {
            addRequest(base); addRequest(base + 1); addRequest(base + 2);
            if (i % 5 == 0) addRequest(base + 3);
        }
    }
}

void Workload::createManual(int values[], int count) {
    int i;
    begin("MANUAL");
    if (count > MAX_WORKLOAD_SIZE) count = MAX_WORKLOAD_SIZE;
    for (i = 0; i < count; i++) addRequest(values[i]);
}

int Workload::getRequestCount() const { return requestCount; }
int Workload::getRequest(int index) const {
    if (index < 0 || index >= requestCount) return 0;
    return requests[index];
}
const char *Workload::getName() const { return name; }
