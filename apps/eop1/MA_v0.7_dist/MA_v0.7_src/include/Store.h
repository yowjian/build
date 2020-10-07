#include <iostream>
#pragma once
#ifndef STORE_H
#define STORE_H
#include <tsl/ordered_map.h>"
#include <string>
using namespace std;
template<typename T>
class Store {
public:
	Store(int MAS) {
		MAX_ALLOWED_SIZE = MAS;
	}
	int size() {
		return currSize;
	}
	void add(const string &id, T entry) {
		map[id] = entry;
		currSize++;
		if (currSize > MAX_ALLOWED_SIZE) {
			delete removeHead();
		}

	}

	T removeHead() {
		T value = map[map.front().first];
		map.erase(map.front().first);
		currSize--;
		return value;
	}
	T remove(const string& id) {
		T value = map[id];
		map.erase(id);
		currSize--;
		return value;
	}
	bool contains(const string& id) {
		auto it = map.find(id);
		if (it != map.end()) {
			return true;
		}
		return false;

	}
	T removeBack() {
		T value = map[map.back().first];
		map.pop_back();
		currSize--;
		return value;
	}
	void print() {
		for (const auto& key_value : map) {
			std::cout << "{" << key_value.first << ", " << key_value.second << "}" << std::endl;
		}
	}
	tsl::ordered_map<string, T>& getMap(){
		return map;
	}
	T get(const string & id) {
		return map[id];
	}
	T get(int index) {
		auto it = map.nth(index);
		if (it != map.end()) {
			return it.value();
		}
		return nullptr;
	}
	T getCurrent() {
		if (currSize > 0) {
			return map[map.front().first];
		}
		return nullptr;
	}
	void clearAll() {
		T value;
		for (const auto& key_value : map) {
			value = key_value.second;
			delete value;
		}
		map.clear();
	}
private:
	int currSize = 0;
	int MAX_ALLOWED_SIZE = -1;
	tsl::ordered_map<string, T> map;

};
#endif