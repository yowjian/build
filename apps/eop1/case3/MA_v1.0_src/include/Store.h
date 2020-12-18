#pragma once
#ifndef STORE_H
#define STORE_H
#include <tsl/ordered_map.h>
#include <string>
#include <mutex> 
#include <iostream>
using namespace std;

template<typename T>
/**
* @brief – Class responsible for all uses of memory of any generic data type as storage in the Mission Application
* Contents must be pointers.
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederick Santiago
* @date – 9/17/2020
*
* @details – MA Store uses tsl's ordered map implementation where insertion matters. Just like a regular map, 
* the data can be access using any data type (such as a string), but the order of insertion is kept and can be 
* accessed as an array using an integer to index the data location. Every entry must be a pointer to an object.
*/
class Store {
public:
	/**
	 * @brief Construct a new Store object
	 * 
	 * @param MAS - MAX ALLOWED SIZE is determined during compilation and if the store entries exceed this parameter's value
	 * the data will be removed from the back (first in).
	 */
	Store(int MAS) {
		MAX_ALLOWED_SIZE = MAS;
	}
	/**
	 * @brief Destroy the Store object and remove all pointers in the tsl map
	 * 
	 */
	~Store() {
		clearAll();
	}
	/**
	 * @brief returns the current size of the ordered map
	 * 
	 * @param VOID
	 *
	 * @return int currentSize of the ordered map
	 */
	int size() {
		return currSize;
	}

	/**
	 * @brief add a new entry to the store at the provided id. Every entry must be a pointer to an object.
	 * 
	 * @param id - unique identifier of the entry, if it already exists, it will be overriden
	 * @param entry - generic data that will be stored in the given identifier
	 *
	 * @return VOID
	 */
	void add(const string &id, T entry) {
		mtx.lock();
		if (contains(id)) {
			mtx.unlock();
			remove(id);
			mtx.lock();
		}
		currSize++;
		map[id] = entry;
		if (currSize > MAX_ALLOWED_SIZE) {
			mtx.unlock();
			removeHead();
			mtx.lock();
		}
		mtx.unlock();
	}
	/**
	 * @brief remove the latest entry from the map
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void removeHead() {
		const std::lock_guard<std::mutex> lock(mtx);
		T value = map[map.front().first];
		map.erase(map.front().first);
		currSize--;
		delete value;
	}
	/**
	 * @brief remvove the entry in the map for the given identifier
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void remove(const string& id) {
		const std::lock_guard<std::mutex> lock(mtx);
		T value = map[id];
		map.erase(id);
		currSize--;
		delete value;
	}
	/**
	 * @brief whether the map contains the given id
	 * 
	 * @param id - unique identifier for the stored data
	 *
	 * @return true if data exists at the given unique identifier
	 * @return false  if data does not exist at the given unique identifier
	 */
	bool contains(const string& id) {
		if (map.empty()) {
			return false;
		}
		if (map.find(id) != map.end()) {
			return true;
		}
		return false;

	}
	/**
	 * @brief remvove the last entry in the map
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void removeBack() {
		const std::lock_guard<std::mutex> lock(mtx);
		T value = map[map.back().first];
		map.pop_back();
		currSize--;
		delete value;
	}
	/**
	 * @brief print all key/value pairs given that value type can directed to the output
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void print() {
		for (const auto& key_value : map) {
			std::cout << "{" << key_value.first << ", " << key_value.second << "}" << std::endl;
		}
	}
	/**
	 * @brief Get the ordered Map object
	 * 
	 * @param VOID
	 *
	 * @return tsl::ordered_map<string, T>& - referrence to an instance of the current map
	 */
	tsl::ordered_map<string, T>& getMap(){
		return map;
	}
	/**
	 * @brief get the value stored at the given id
	 * 
	 * @param id - unique string identifer
	 *
	 * @return T - generic data determined when the Store is initialized
	 */
	T get(const string & id) {
		if (map.empty()) {
			return nullptr;
		}
		auto it = map.find(id);
		if (it != map.end()) {
			return it.value();
		}
		return nullptr;
	}
	/**
	 * @brief get the data/value at the provided index from the map
	 * 
	 * @param index - data at given index sorted based on order of entry
	 *
	 * @return T - value at given index
	 */
	T get(int index) {
		if (map.empty()) {
			return nullptr;
		}
		auto it = map.nth(index);
		if (it != map.end()) {
			return it.value();
		}
		return nullptr;
	}
	/**
	 * @brief Get the latest entry to the map
	 * 
	 * @param VOID
	 *
	 * @return T - get the data at end of the map
	 */
	T getCurrent() {
		if (!map.empty()) {
			return map[map.back().first];
		}
		return nullptr;
	}
	/**
	 * @brief Get the first/beginning value of the map.
	 * 
	 * @param VOID
	 *
	 * @return T - get the data at the head/beginning of the map
	 */
	T getHead() {
		if (!map.empty()) {
			return map[map.front().first];
		}
		return nullptr;
	}
	/**
	 * @brief delete all pointers and remove the references from the map
	 * 
	 * @param VOID
	 * 
	 * @return VOID
	 */
	void clearAll() {
		const std::lock_guard<std::mutex> lock(mtx);
		T value;
		for (const auto& key_value : map) {
			value = key_value.second;
			delete value;
		}
		map.clear();
		currSize = 0;
	}
	/**
	 * @brief set new max size, remove items if new size is less
	 * than previous size
	 *
	 * @param size - new size to be used as the MAS
	 *
	 * @return VOID
	 */
	void setSize(int size) {
		mtx.lock();
		if (size > 0 && size < currSize) {
			while (size != currSize) {
				removeHead();
			}
			MAX_ALLOWED_SIZE = size;
		}
		mtx.unlock();
	}
private:
	/**
	 * @brief current size of the map. 
	 * 
	 */
	int currSize = 0;
	/**
	 * @brief max allowed size of the map before data from the front is removed
	 * 
	 */
	int MAX_ALLOWED_SIZE = -1;
	/**
	 * @brief hash map sorted based on order of insertion
	 * 
	 */
	tsl::ordered_map<string, T> map;
	/**
	 * @brief mutex to protect multiple threads from writing / removing at the same time
	 * 
	 */
	std::mutex mtx;

};
#endif