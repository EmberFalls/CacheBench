#include <iostream.h>
#include <stdio.h>
#include "WORKLOAD.H"
#include "BENCH.H"
#include "CACHE.H"
#include "LRU.H"
#include "LFU.H"
#include "SECOND.H"
#include "HYBRID.H"

static const char *RESULTS_FILE = "C:\\TURBOC3\\OOPS-C~1\\RESULTS.TXT";

static Workload workload;
static int manualValues[MAX_WORKLOAD_SIZE];

void printMenu() {
    cout << "\n========== CACHEBENCH ==========" << endl;
    cout << "1. Enter Manual Workload" << endl;
    cout << "2. Use Repeated Workload" << endl;
    cout << "3. Use Changing Workload" << endl;
    cout << "4. Use Mixed Workload" << endl;
    cout << "5. Use Burst Workload" << endl;
    cout << "6. Run One Policy" << endl;
    cout << "7. Benchmark All Policies" << endl;
    cout << "8. View Saved Benchmark Results" << endl;
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

void writePolicyResult(FILE *output, const Workload &selectedWorkload,
                       int capacity, CachePolicy *policy) {
    Cache cache(capacity, policy);
    int i;

    for (i = 0; i < selectedWorkload.getRequestCount(); i++)
        cache.processRequest(selectedWorkload.getRequest(i));

    const Metrics &metrics = cache.getMetrics();
    fprintf(output, "%-22s%6d%8d%11d%9.1f%%\n",
            metrics.getPolicyName(), metrics.getHits(), metrics.getMisses(),
            metrics.getEvictions(), metrics.getHitRatio());
}

int appendBenchmark(const Workload &selectedWorkload, int capacity,
                    int allPolicies, int selectedPolicy) {
    FILE *output = fopen(RESULTS_FILE, "a");
    if (output == NULL) return 0;

    fprintf(output, "\nWorkload: %s\n", selectedWorkload.getName());
    fprintf(output, "Cache Capacity: %d\n", capacity);
    fprintf(output, "Total Requests: %d\n\n",
            selectedWorkload.getRequestCount());
    fprintf(output, "Policy                 Hits  Misses  Evictions  Hit Ratio\n");
    fprintf(output, "---------------------------------------------------------\n");

    if (allPolicies) {
        LRUPolicy lru;
        LFUPolicy lfu;
        SecondChancePolicy secondChance;
        AdaptiveHybridPolicy adaptive;

        writePolicyResult(output, selectedWorkload, capacity, &lru);
        writePolicyResult(output, selectedWorkload, capacity, &lfu);
        writePolicyResult(output, selectedWorkload, capacity, &secondChance);
        writePolicyResult(output, selectedWorkload, capacity, &adaptive);
    } else if (selectedPolicy == 1) {
        LRUPolicy policy;
        writePolicyResult(output, selectedWorkload, capacity, &policy);
    } else if (selectedPolicy == 2) {
        LFUPolicy policy;
        writePolicyResult(output, selectedWorkload, capacity, &policy);
    } else if (selectedPolicy == 3) {
        SecondChancePolicy policy;
        writePolicyResult(output, selectedWorkload, capacity, &policy);
    } else if (selectedPolicy == 4) {
        AdaptiveHybridPolicy policy;
        writePolicyResult(output, selectedWorkload, capacity, &policy);
    }

    fprintf(output, "\n");
    fclose(output);
    return 1;
}

void showSavedResults() {
    FILE *input = fopen(RESULTS_FILE, "r");
    char line[128];

    if (input == NULL) {
        cout << "No saved benchmark results found yet." << endl;
        return;
    }

    cout << "\nSaved benchmark results:\n" << endl;
    while (fgets(line, sizeof(line), input) != NULL) cout << line;
    fclose(input);
}

void runSingle(const Workload &selectedWorkload, int capacity) {
    int choice;
    int validChoice = 1;
    int saved;
    cout << "\n1. LRU\n2. LFU\n3. Second-Chance\n4. Adaptive Hybrid\nChoose policy: ";
    cin >> choice;
    BenchmarkEngine engine(selectedWorkload, capacity);
    if (choice == 1) {
        LRUPolicy policy;
        engine.runOne(&policy);
    } else if (choice == 2) {
        LFUPolicy policy;
        engine.runOne(&policy);
    } else if (choice == 3) {
        SecondChancePolicy policy;
        engine.runOne(&policy);
    } else if (choice == 4) {
        AdaptiveHybridPolicy policy;
        engine.runOne(&policy);
    } else {
        cout << "Invalid policy selection." << endl;
        validChoice = 0;
    }
    if (validChoice) {
        engine.printReport();
        saved = appendBenchmark(selectedWorkload, capacity, 0, choice);
        if (saved) cout << "Results appended to RESULTS.TXT." << endl;
        else cout << "Could not write RESULTS.TXT." << endl;
    }
}

int main() {
    int choice = 0;
    int capacity;
    int count, i;
    int saved;
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
            for (i = 0; i < count; i++) cin >> manualValues[i];
            workload.createManual(manualValues, count);
            cout << "Manual workload loaded." << endl;
        } else if (choice == 2) {
            workload.createRepeated();
            cout << "Repeated workload loaded." << endl;
        } else if (choice == 3) {
            workload.createChanging();
            cout << "Changing workload loaded." << endl;
        } else if (choice == 4) {
            workload.createMixed();
            cout << "Mixed workload loaded." << endl;
        } else if (choice == 5) {
            workload.createBurst();
            cout << "Burst workload loaded." << endl;
        } else if (choice == 6) {
            if (workload.getRequestCount() == 0) {
                cout << "Load a workload first." << endl;
                continue;
            }
            capacity = readCapacity();
            runSingle(workload, capacity);
        } else if (choice == 7) {
            if (workload.getRequestCount() == 0) {
                cout << "Load a workload first." << endl;
                continue;
            }
            capacity = readCapacity();
            {
                BenchmarkEngine engine(workload, capacity);
                engine.runAll();
                engine.printReport();
            }
            saved = appendBenchmark(workload, capacity, 1, 0);
            if (saved) cout << "Results appended to RESULTS.TXT." << endl;
            else cout << "Could not write RESULTS.TXT." << endl;
        } else if (choice == 8) {
            showSavedResults();
        } else if (choice != 9) {
            cout << "Invalid selection." << endl;
        }
    }
    cout << "Goodbye." << endl;
    return 0;
}
