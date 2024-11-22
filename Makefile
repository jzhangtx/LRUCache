LRUCache: LRUCache.o
	g++ -g -o LRUCache.exe LRUCache.o -pthread    

LRUCache.o: LRUCache/LRUCache.cpp
	g++ -g  -c -pthread LRUCache/LRUCache.cpp
