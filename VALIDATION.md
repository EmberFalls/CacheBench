# Validation cases

Use the **Manual Workload** menu option with the following inputs. These compact cases make the simulator's accounting and replacement behavior easy to check by hand.

| Cache capacity | Request sequence | Policy | Expected hits | Expected misses | Expected evictions |
|---:|---|---|---:|---:|---:|
| 2 | `1 2 1 3 2` | LRU | 1 | 4 | 2 |
| 2 | `1 2 1 3 2` | LFU | 1 | 4 | 2 |
| 2 | `1 2 1 3 2` | Second-Chance | 1 | 4 | 2 |
| 2 | `1 2 1 3 2` | Adaptive Hybrid | 1 | 4 | 2 |
| 3 | `1 2 3 1 2 4 3` | LRU | 2 | 5 | 2 |
| 3 | `1 2 3 1 2 4 3` | LFU | 3 | 4 | 1 |
| 3 | `1 2 3 1 2 4 3` | Second-Chance | 3 | 4 | 1 |
| 3 | `1 2 3 1 2 4 3` | Adaptive Hybrid | 2 | 5 | 2 |

For the second case, key `3` is the least frequently used entry when key `4` arrives. LFU and Second-Chance therefore retain it and hit on the final request, while LRU evicts it. The adaptive score assigns a greater retention value to the two frequently accessed entries, then later replaces the newly inserted low-frequency key; its measured result is shown rather than presented as universally better.
