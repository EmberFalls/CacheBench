#include "ENTRY.H"

CacheEntry::CacheEntry() { reset(); }

void CacheEntry::reset() {
    key = 0;
    frequency = 0;
    lastAccessTime = 0;
    insertionTime = 0;
    referenceBit = 0;
    valid = 0;
}

void CacheEntry::insert(int newKey, int currentTime) {
    key = newKey;
    frequency = 1;
    lastAccessTime = currentTime;
    insertionTime = currentTime;
    referenceBit = 1;
    valid = 1;
}

void CacheEntry::markAccess(int currentTime) {
    frequency++;
    lastAccessTime = currentTime;
    referenceBit = 1;
}

int CacheEntry::getKey() const { return key; }
int CacheEntry::getFrequency() const { return frequency; }
int CacheEntry::getLastAccessTime() const { return lastAccessTime; }
int CacheEntry::getInsertionTime() const { return insertionTime; }
int CacheEntry::getReferenceBit() const { return referenceBit; }
int CacheEntry::isValid() const { return valid; }
void CacheEntry::clearReferenceBit() { referenceBit = 0; }
