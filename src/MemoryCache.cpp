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
	count_hit = 0;
	hit = false;

	myFile.open("mem.bin", ios::in | ios::out | ios::binary); 
}

long MemoryCache::LRUReplacement () {
	double min = 99999999999999;
	long evict_index = -1;
	for (unsigned int i = 0; i < num_pages; i++) {
		if (last_used[i] < min) {
			min = last_used[i];
			evict_index = i;
		}
	}
	return evict_index;
} 

long MemoryCache::HandleCacheMiss () {
	long evict_index = -1;
	if (std::find(tag.begin(), tag.end(), -1) != tag.end()) { // if cache has space
		std::vector<long>::iterator it; 
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


void MemoryCache::WritePageToCache (int index, long cache_index) {
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

char MemoryCache::FACache(long addr, int value, int instruction) {
	long cache_index = addr / page_size;
	long page_index = addr % page_size;
	int evict_index; // index where page is to be brought

	// searching the address in tag
	hit = false;
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
		return cache[evict_index][page_index];
	}
	else if (instruction == 1) { // for store instruction, update the last used value and dirty bit
		cache[evict_index][page_index] = value;
		last_used[evict_index] = std::chrono::duration<double, std::milli> (std::chrono::high_resolution_clock::now() - start_time).count();
		dirty[evict_index] = true;
		return -1;
	}
}

int MemoryCache::getByte (long addr) {
	int result = (int)MemoryCache::FACache(addr, -1, 0);
	if (hit) {
		count_hit++;
	}
	return result;
}

void MemoryCache::setByte (long addr, int value) {
	int result = (int)MemoryCache::FACache (addr, value, 1);
	if (hit) {
		count_hit++;
	}
	return;
}


int MemoryCache::getHalfWord (long addr) {
	unsigned char res[2];
	bool is_hit[2];
	res[0] = MemoryCache::FACache(addr, -1, 0);
	is_hit[0] = hit;
	res[1] = MemoryCache::FACache(addr + 1, -1, 0);
	is_hit[1] = hit;
	int result = res[1] | (res[0] << 8); 
	CheckHit(is_hit, 2);
	return result;
}

void MemoryCache::setHalfWord (long addr, int value) {
	unsigned char res[2];
	bool is_hit[2];
    res[0] = (value >> 8) & 0xFF;
    res[1] = value & 0xFF;
	char result = MemoryCache::FACache (addr, (int)res[0], 1);
	is_hit[0] = hit;
	char result2 = MemoryCache::FACache (addr + 1, (int)res[1], 1);
	is_hit[1] = hit;
	CheckHit(is_hit, 2);
	return;
}

int MemoryCache::getWord (long addr) {
	unsigned char res[4];
	bool is_hit[4];
	for (int i = 0; i < 4; i++) {
		res[i] = MemoryCache::FACache(addr + i, -1, 0);
		is_hit[i] = hit;
	}
	int result = res[3] | (res[2] << 8) | (res[1] << 16) | (res[0] << 24);
	CheckHit(is_hit, 4);
	return result;
}

void MemoryCache::setWord (long addr, int value) {
	unsigned char res[4];
	bool is_hit[4];
	res[0] = (value >> 24) & 0xFF;
    res[1] = (value >> 16) & 0xFF;
    res[2] = (value >> 8) & 0xFF;
    res[3] = value & 0xFF;

    for (int i = 0; i < 4; i++) {
    	char result = MemoryCache::FACache (addr + i, (int)res[i], 1);
		is_hit[i] = hit;
    }
	CheckHit(is_hit, 4);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////
long MemoryCache::getDoubleWord (long addr) {
	unsigned char res[8];
	bool is_hit[8];
	// cout << "MEM::GET(LOAD)  " << addr << " ---- ";
	for (int i = 0; i < 8; i++) {
		res[i] = MemoryCache::FACache(addr + i, -1, 0);
		is_hit[i] = hit;
		// cout << int(res[i]) << " ";
	}
	long result = (long)res[7] | (long)res[6] << 8 | (long)res[5] << 16 | (long)res[4] << 24 | (long)res[3] << 32 | (long)res[2] << 40 | (long)res[1] << 48 | (long)res[0] << 56;
	// cout << endl << result << endl << "-----" << endl;
	CheckHit(is_hit, 8);
	return result;
}

void MemoryCache::setDoubleWord (long addr, long value) {
	unsigned char res[8];
	bool is_hit[8];
	// cout << "MEM::SET(STORE)  " << addr << " .. " << value << " ----- ";
	res[0] = (value >> 56) & 0xFFFF;
    res[1] = (value >> 48) & 0xFFFF;
    res[2] = (value >> 40) & 0xFFFF;
    res[3] = (value >> 32) & 0xFFFF;
    res[4] = (value >> 24) & 0xFFFF;
    res[5] = (value >> 16) & 0xFFFF;
    res[6] = (value >> 8) & 0xFFFF;
    res[7] = value & 0xFFFF;

    for (int i = 0; i < 8; i++) {
    	// cout << (int)res[i] << " ";
    	char result = MemoryCache::FACache (addr + i, (int)res[i], 1);
		is_hit[i] = hit;
    }
    // cout << endl;
	CheckHit(is_hit, 8);
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////

void MemoryCache::CheckHit (bool is_hit[], int size) {
	bool temp = true;
	for (int i = 0; i < size; i++) {
		temp = temp && is_hit[i];
	}
	if (temp) count_hit++;
}

int MemoryCache::GetHits () {
	return count_hit;
}

double MemoryCache::FindTimeTaken () {
	return std::chrono::duration<double, std::milli> (std::chrono::high_resolution_clock::now() - start_time).count();
}

void MemoryCache::WriteBackToMem () { // write all the dirty pages back to the file at the end
	for (int k = 0; k < num_pages; k++) {
		if (dirty[k]) {
			MemoryCache::WritePageToMem (k);
		}
	}
}