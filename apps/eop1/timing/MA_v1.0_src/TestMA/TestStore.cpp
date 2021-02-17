#include "TestStore.h"
#include <iostream>
#include <string>
#include <list>
#include <Utils.h>
#include <string>
#include <Store.h>
#include <tsl/ordered_map.h>"

Store<string *> store(5);

void TestStore::testAdd(void)
{
	CPPUNIT_ASSERT_EQUAL(store.size(), 0);
	string expected = "test";
	string *test = new string(expected);
	store.add("1", test);
	string actual = store.get("1")->data();
	CPPUNIT_ASSERT_EQUAL(actual, expected);
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	store.clearAll();
}

void TestStore::testClearAll(void)
{
	string *first = new string("first");
	string *second = new string("second");
	store.add("1", first);
	store.add("2", second);
	int num = 1;
	for (const auto& key_value : store.getMap()) {
		CPPUNIT_ASSERT_EQUAL(key_value.first, std::to_string(num));
		num++;
	}
	store.clearAll();
	CPPUNIT_ASSERT_EQUAL(store.size(), 0);
	CPPUNIT_ASSERT_EQUAL(store.getMap().empty(), true);

}

void TestStore::testRemove(void) {
	string expected = "test";
	string *test = new string(expected);
	store.add("test", test);
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), true);
	store.remove(expected);
	CPPUNIT_ASSERT_EQUAL(store.size(), 0);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), false);
	store.clearAll();

}

void TestStore::testOverride(void) {
	string *first = new string("first");
	string *second = new string("second");
	store.add("test", first);
	CPPUNIT_ASSERT_EQUAL(store.get("test")->data(), first->data());
	store.add("test", second);
	CPPUNIT_ASSERT_EQUAL(store.get("test")->data(), second->data());
	store.clearAll();
}

void TestStore::testGetIndex(void) {
	string *first = new string("first");
	string *second = new string("second");
	string *third = new string("third");
	store.add("1", first);
	store.add("2", second);
	store.add("3", third);
	CPPUNIT_ASSERT_EQUAL(store.getCurrent()->data(), third->data());
	CPPUNIT_ASSERT_EQUAL(store.get(1)->data(), second->data());
	CPPUNIT_ASSERT_EQUAL(store.get("1")->data(), first->data());
	store.clearAll();
}

void TestStore::testSize(void) {
	CPPUNIT_ASSERT_EQUAL(store.size(), 0);
	string *first = new string("first");
	store.add("1", first);
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	string *second = new string("second");
	store.add("2", second);
	CPPUNIT_ASSERT_EQUAL(store.size(), 2);
	store.remove("2");
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	store.clearAll();
}

void TestStore::testRemoveHead(void) {
	string expected = "test";
	string *test = new string(expected);
	string *test2 = new string("test2");
	store.add("test", test);
	store.add("test2", test2);
	CPPUNIT_ASSERT_EQUAL(store.size(), 2);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), true);
	store.removeHead();
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), false);
	store.clearAll();
}

void TestStore::testRemoveBack(void) {
	string expected = "test2";
	string *test = new string("test");
	string *test2 = new string(expected);
	store.add("test", test);
	store.add("test2", test2);
	CPPUNIT_ASSERT_EQUAL(store.size(), 2);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), true);
	store.removeBack();
	CPPUNIT_ASSERT_EQUAL(store.size(), 1);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), false);
	store.clearAll();
}

void TestStore::testContains(void) {
	string expected = "test";
	string notExpected = "test2";
	string *test = new string(expected);
	store.add("test", test);
	CPPUNIT_ASSERT_EQUAL(store.contains(expected), true);
	CPPUNIT_ASSERT_EQUAL(store.contains(notExpected), false);
	store.clearAll();
}

void TestStore::testGetMap(void) {
	string str = "test";
	string *test = new string(str);
	store.add("test", test);
	auto *ptr = &store.getMap();
	CPPUNIT_ASSERT(ptr != nullptr);
}
