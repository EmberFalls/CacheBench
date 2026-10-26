#ifndef WORKLOAD_H
#define WORKLOAD_H

#define MAX_WORKLOAD_SIZE 500

class Workload {
private:
    int requests[MAX_WORKLOAD_SIZE];
    int requestCount;
    char name[32];
    void begin(const char *newName);
    void addRequest(int key);

public:
    Workload();
    void createRepeated();
    void createChanging();
    void createMixed();
    void createBurst();
    void createManual(int values[], int count);
    int getRequestCount() const;
    int getRequest(int index) const;
    const char *getName() const;
};

#endif
