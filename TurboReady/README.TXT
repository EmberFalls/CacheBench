CACHEBENCH TURBO C++ VERSION

Copy all .CPP and .H files from this folder into one short folder, for example C:\CACHE.
This copy uses filenames that fit the DOS 8.3 limit.

In Turbo C++ Options > Directories, set Include Directories to:
C:\TURBOC3\INCLUDE;C:\CACHE

Create a project and add these source files:
MAIN.CPP ENTRY.CPP CACHE.CPP METRICS.CPP WORKLOAD.CPP BENCH.CPP
LRU.CPP LFU.CPP SECOND.CPP HYBRID.CPP

Do not add .H files as project source files. They are included by the .CPP files.
Choose Project > Build All, then Run (Ctrl+F9). No command-line arguments are needed.

The maximum manual workload is 500 requests. The built-in workloads use at most 400.
