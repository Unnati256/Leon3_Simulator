#include <iostream>
#include <chrono>
#include<vector>
#include <algorithm>
#include "../include/MemoryCache.h"
using namespace std;

MemoryCache::MemoryCache () {
	cache_size = 262144; // 256K
	page_size = 4096; // 4K
	num_pages = cache_size / page_size;
	start_time = std::chrono::high_resolution_clock::now();	
	cache.resize(num_pages, vector<unsigned char>(page_size, 0));

	// initialized tag and last_used to -1
	last_used.resize(num_pages, -1);
	tag.resize(num_pages, -1);
	dirty.resize(num_pages, false);

	myFile.open("mem.bin", ios::in | ios::out | ios::binary); 
}

long MemoryCache::LRUReplacement () {
	double min = 99999999999999;
	int evict_index = -1;
	for (unsigned int i = 0; i < num_pages; i++) {
		if (last_used[i] < min) {
			min = last_used[i];
			evict_index = i;
		}
	}
	return evict_index;
} 

int MemoryCache::HandleCacheMiss () {
	int evict_index = -1;
	if (std::find(tag.begin(), tag.end(), -1) != tag.end()) { // if cache has space
		std::vector<int>::iterator it; 
		it = std::find(tag.begin(), tag.end(), -1);
		evict_index = std::distance(tag.begin(), it);
		return evict_index;
	}
	else { // else find the page to be replaced
		evict_index = MemoryCache::LRUReplacement();
	}
	return evict_index; // return the index of the page
}

void MemoryCache::WritePageToMem (int evict_index) {
	unsigned char temp[page_size];
	for (int i = 0; i < page_size; i++) {
    	temp[i] = cache[evict_index][i];
    }
	long seek_add = tag[evict_index] * page_size;
	for (int i = 0; i < page_size; i++) {
    	myFile.seekp(seek_add, ios::beg);
    	myFile.write(reinterpret_cast< char *>(&temp[i]), sizeof(temp[0]));
    	seek_add++;
    }
    dirty[evict_index] = false;
}


void MemoryCache::WritePageToCache (int index, int cache_index) {
	unsigned char temp[page_size];
	long seek_addr = cache_index * page_size; // changed now
	myFile.seekg(seek_addr, ios::beg);
	myFile.read(reinterpret_cast< char *>(temp), sizeof(temp));
	for (int i = 0; i < page_size; i++) {
		cache[index][i] = temp[i];
	}
	tag[index] = cache_index;
	dirty[index] = false;
	return;
}

int MemoryCache::FACache(long addr, int value, int instruction) {
	int cache_index = addr / page_size;
	int page_index = addr % page_size;
	int evict_index; // index where page is to be brought

	// searching the address in tag
	bool hit = false;
	for (unsigned int i = 0; i < num_pages; i++) {
		if (tag[i] == cache_index) { // if cache hit
			evict_index = i;
			hit = true;
			break;
		}
	}

	// if cache miss	
	if (!hit) {
		evict_index = MemoryCache::HandleCacheMiss (); // find the index where page is to be brought
		
		if (dirty[evict_index]) { // write the page back to mem if the page to be replaced is dirty
			MemoryCache::WritePageToMem (evict_index);
		}
		MemoryCache::WritePageToCache (evict_index, cache_index); // write the required page in cache
	}

	if (instruction == 0) { // for load instruction, update the last used
		last_used[evict_index] = std::chrono::duration<double, std::milli> (std::chrono::high_resolution_clock::now() - start_time).count();
		return int(cache[evict_index][page_index]);
	}
	else if (instruction == 1) { // for store instruction, update the last used value and dirty bit
		cache[evict_index][page_index] = value;
		last_used[evict_index] = std::chrono::duration<double, std::milli> (std::chrono::high_resolution_clock::now() - start_time).count();
		dirty[evict_index] = true;
		return -1;
	}
}

int MemoryCache::getByte (int addr) {
	int result = MemoryCache::FACache(addr, -1, 0);
	return result;
}

void MemoryCache::setByte (int addr, int value) {
	int result = MemoryCache::FACache (addr, value, 1);
	return;
}

void MemoryCache::WriteBackToMem () { // write all the dirty pages back to the file at the end
	for (int k = 0; k < num_pages; k++) {
		if (dirty[k]) {
			MemoryCache::WritePageToMem (k);
		}
	}
}