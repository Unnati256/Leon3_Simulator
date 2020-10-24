#ifndef MEMORYCACHE_H
#define MEMORYCACHE_H

#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>


class MemoryCache {
private:
	long cache_size;
	long page_size;
	std::vector<std::vector<unsigned char>> cache; // 2d vector: cache[cache_size/page_size][page_size];
	long num_pages; //cache_size / page_size
	std::vector<double> last_used; // to track when the page was last used (for LRU policy)
	std::vector<int> tag; // the tag array
	std::vector<bool> dirty; // to maintain dirty bit
	std::chrono::high_resolution_clock::time_point start_time;
	std::fstream myFile;

public:
	MemoryCache();
	int FACache (long addr, int value, int instruction);
	long LRUReplacement ();
	int HandleCacheMiss ();
	void WritePageToMem (int evict_index);
	void WritePageToCache (int index, int cache_index);
	int getByte (int addr);
	void setByte (int addr, int value);
	void WriteBackToMem ();
};


#endif