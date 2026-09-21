#include <iostream.h>
#include <conio.h>
#include "Workload.h"
#include "BenchmarkEngine.h"
#include "LRUPolicy.h"
#include "LFUPolicy.h"
#include "SecondChancePolicy.h"
#include "AdaptiveHybridPolicy.h"

void printMenu() {
    cout << "\n========== CACHEBENCH ==========" << endl;
    cout << "1. Enter Manual Workload" << endl;
    cout << "2. Use Repeated Workload" << endl;
    cout << "3. Use Changing Workload" << endl;
    cout << "4. Use Mixed Workload" << endl;
    cout << "5. Use Burst Workload" << endl;
    cout << "6. Run One Policy" << endl;
    cout << "7. Benchmark All Policies" << endl;
    cout << "8. View OOP/Policy Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

int readCapacity() {
    int capacity;
    cout << "Cache capacity (1-" << MAX_CACHE_SIZE << "): ";
    cin >> capacity;
    if (capacity < 1) capacity = 1;
    if (capacity > MAX_CACHE_SIZE) capacity = MAX_CACHE_SIZE;
    return capacity;
}

void printInfo() {
    cout << "\nOOP design:" << endl;
    cout << "CacheEntry encapsulates item metadata." << endl;
    cout << "CachePolicy is an abstract base class." << endl;
    cout << "LRU, LFU, Second-Chance, and Adaptive Hybrid inherit from it." << endl;
    cout << "Cache calls chooseVictim through a CachePolicy pointer (runtime polymorphism)." << endl;
    cout << "Adaptive Hybrid retains entries using frequency (60%) and normalized recency (40%)." << endl;
    cout << "LFU ties are resolved by oldest last-access time." << endl;
}

void runSingle(const Workload &workload, int capacity) {
    int choice;
    cout << "\n1. LRU\n2. LFU\n3. Second-Chance\n4. Adaptive Hybrid\nChoose policy: ";
    cin >> choice;
    BenchmarkEngine engine(workload, capacity);
    if (choice == 1) {
        LRUPolicy policy; engine.runOne(&policy);
    } else if (choice == 2) {
        LFUPolicy policy; engine.runOne(&policy);
    } else if (choice == 3) {
        SecondChancePolicy policy; engine.runOne(&policy);
    } else if (choice == 4) {
        AdaptiveHybridPolicy policy; engine.runOne(&policy);
    } else {
        cout << "Invalid policy selection." << endl;
        return;
    }
    engine.printReport();
}

int main() {
    Workload workload;
    int choice = 0;
    int capacity;
    int count, values[MAX_WORKLOAD_SIZE], i;
    cout << "CacheBench: Cache Replacement Simulator" << endl;
    while (choice != 9) {
        printMenu();
        cin >> choice;
        if (choice == 1) {
            cout << "Number of requests (1-" << MAX_WORKLOAD_SIZE << "): ";
            cin >> count;
            if (count < 1) count = 1;
            if (count > MAX_WORKLOAD_SIZE) count = MAX_WORKLOAD_SIZE;
            cout << "Enter " << count << " integer keys: ";
            for (i = 0; i < count; i++) cin >> values[i];
            workload.createManual(values, count);
            cout << "Manual workload loaded." << endl;
        } else if (choice == 2) {
            workload.createRepeated(); cout << "Repeated workload loaded." << endl;
        } else if (choice == 3) {
            workload.createChanging(); cout << "Changing workload loaded." << endl;
        } else if (choice == 4) {
            workload.createMixed(); cout << "Mixed workload loaded." << endl;
        } else if (choice == 5) {
            workload.createBurst(); cout << "Burst workload loaded." << endl;
        } else if (choice == 6) {
            if (workload.getRequestCount() == 0) { cout << "Load a workload first." << endl; continue; }
            capacity = readCapacity(); runSingle(workload, capacity);
        } else if (choice == 7) {
            if (workload.getRequestCount() == 0) { cout << "Load a workload first." << endl; continue; }
            capacity = readCapacity();
            { BenchmarkEngine engine(workload, capacity); engine.runAll(); engine.printReport(); }
        } else if (choice == 8) printInfo();
        else if (choice != 9) cout << "Invalid selection." << endl;
    }
    cout << "Goodbye." << endl;
    return 0;
}
