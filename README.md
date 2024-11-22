LRU Cache


Implement Least Recently Used (LRU) cache.

You need to implement the following for the LRUCache class:

LRUCache(int capacity) initializes the cache to store data of size: capacity.
int get(int key) returns the value of the key if it exists, otherwise returns -1.
void add(int key, int value) updates the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Note: Try to achieve each operation in O(1) time complexity.

Testing
Input Format
The first line contains two space-separated integers capacity and numQueries.

The next numQueries lines have 2 space-separated integers, x and y.
If x = -1, get the value of key y. Else, add the key x with value y.

Output Format
Space-separated results of int get(int key).

Sample Input
3 11
-1 1
1 5
2 6
3 7
-1 1
1 8
-1 1
4 9
-1 2
-1 3
-1 4
Expected Output
-1 5 8 -1 7 9