# CacheBench

An object-oriented cache replacement simulator designed for Turbo C++ style C++.

## Build in Turbo C++

Create a project and add every `.cpp` file in this directory. Compile and run `main.cpp`. The project intentionally uses fixed arrays, character arrays, virtual functions, and classic `<iostream.h>` headers rather than STL containers or modern C++ features.

## Policies

- **LRU:** evicts the least recently accessed entry.
- **LFU:** evicts the least frequently accessed entry; ties use the oldest last access.
- **Second-Chance:** uses a persistent clock pointer and reference bits.
- **Adaptive Hybrid:** retains entries by a weighted score: frequency 60% and normalized recency 40%; its lowest score is evicted.

The same selected workload is replayed from the beginning for every policy, making each comparison fair.

## Modern compiler note

For GCC/Clang, replace `<iostream.h>` with `<iostream>`, `<iomanip.h>` with `<iomanip>`, `<conio.h>` may be removed, and add `using namespace std;`. These substitutions are not needed in Turbo C++.
