#ifndef CACHEENTRY_H
#define CACHEENTRY_H

class CacheEntry {
private:
    int key;
    int frequency;
    int lastAccessTime;
    int insertionTime;
    int referenceBit;
    int valid;

public:
    CacheEntry();
    void reset();
    void insert(int newKey, int currentTime);
    void markAccess(int currentTime);
    int getKey() const;
    int getFrequency() const;
    int getLastAccessTime() const;
    int getInsertionTime() const;
    int getReferenceBit() const;
    int isValid() const;
    void clearReferenceBit();
};

#endif
