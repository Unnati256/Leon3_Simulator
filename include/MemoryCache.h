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
	std::vector<long> tag; // the tag array
	std::vector<bool> dirty; // to maintain dirty bit
	std::chrono::high_resolution_clock::time_point start_time;
	std::fstream myFile;
	long count_hit;
	bool hit;

public:
	MemoryCache();
	char FACache (long addr, int value, int instruction);
	long LRUReplacement ();
	long HandleCacheMiss ();
	void WritePageToMem (int evict_index);
	void WritePageToCache (int index, long cache_index);

	int getByte (long addr);
	void setByte (long addr, int value);
	int getHalfWord (long addr);
	void setHalfWord (long addr, int value);
	int getWord (long addr);
	void setWord (long addr, int value);
	long getDoubleWord (long addr);
	void setDoubleWord (long addr, long value);
	
	int GetHits ();
	double FindTimeTaken ();
	void CheckHit (bool is_hit[], int size);
	void WriteBackToMem ();
};


#endif