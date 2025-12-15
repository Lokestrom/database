#include "String.hpp"
#include <cassert>
#include <iostream>

#if DATABASE_EXCEPTIONS_ENABLED == 0
#error tests must be compiled with exceptions
#endif

using namespace Database;

void checkString(const String& str, const char* expected) {
	assert(str.length() == strlen(expected) && "String length does not match expected length");
	assert(str.capacity() >= str.length() && "String capacity is less than length");
	for (size_t i = 0; i < str.length(); i++) {
		assert(str[i] == expected[i] && "String character does not match expected character");
	}
	assert(str.cstr()[str.length()] == '\0' && "string not 0 terminated");
}

void testConstructor() {
	String strDefault;
	checkString(strDefault, "");
	strDefault = "Hello World";

	String strCopy(strDefault);
	checkString(strCopy, "Hello World");

	String strMove(std::move(strDefault));
	checkString(strMove, "Hello World");
	assert(strDefault.cstr() == nullptr);

	std::string stdStr = "Hello";
	String strStdStr(stdStr);
	checkString(strStdStr, "Hello");
	
	String str2("Hello");
	checkString(str2, "Hello");
}

void testAssignment() {
	String temp("Hello");
	String strDefault;
	strDefault = temp;
	checkString(strDefault, "Hello");

	String strMoveAssign;
	strMoveAssign = std::move(temp);
	checkString(strMoveAssign, "Hello");
	assert(temp.cstr() == nullptr);

	String strStd;
	strStd = std::string("World");
	checkString(strStd, "World");

	String strCstr;
	strCstr = "Test";
	checkString(strCstr, "Test");
}

void testInsert() {
	String str("Hello");
	str.insert(5, " World");
	checkString(str, "Hello World");

	str.insert(0, 'A');
	checkString(str, "AHello World");

	str.insert(6, String(","));
	checkString(str, "AHello, World");

	str.insert(6, " Beautiful bad", 10);
	checkString(str, "AHello Beautiful, World");

	str.pushBack('!');
	checkString(str, "AHello Beautiful, World!");
}

void testPop() {
	String str("Hello");
	str.popBack();
	checkString(str, "Hell");

	str.pop(1);
	checkString(str, "Hll");

	str.pop(0, 2);
	checkString(str, "l");
}

void testSearch() {
	String str("abracadabra");
	assert(str.contains("cad") == true);
	assert(str.contains("xyz") == false);

	assert(str.linearSearch('a') == 0);
	assert(str.linearSearch('z') == str.length());
	assert(str.linearSearchR('a') == 10);

	assert(str.linearSearch("ab") == 0);
	assert(str.linearSearch("abc") == str.length());
	assert(str.linearSearchR("ca") == 4);

	String sortedStr("abbbbbcdefffffghijklm");
	assert(sortedStr.binarySearch('c') == 6);
	assert(sortedStr.binarySearch('y') == sortedStr.length());
}

void testSort() {
	String str("ddbcca");
	str.mergeSort();
	checkString(str, "abccdd");
	String str2("edcbbaa");
	str2.bubbleSort();
	checkString(str2, "aabbcde");
}

void removeTests() {
	String str("abracadabra");
	str.remove('a', 2);
	checkString(str, "brcadabra");
	str.remove('b');
	checkString(str, "rcadara");
}

void testSplit() {
	String str("one,two,three,,four,");
	auto parts = str.split(',');
	assert(parts.size() == 4);
	checkString(parts[0], "one");
	checkString(parts[1], "two");
	checkString(parts[2], "three");
	checkString(parts[3], "four");


	String str2("::one::two::three:::four::");
	parts = str2.split("::");
	assert(parts.size() == 4);
	checkString(parts[0], "one");
	checkString(parts[1], "two");
	checkString(parts[2], "three");
	checkString(parts[3], ":four");
}

void testConvertions(){
	String a = toS(1);
	checkString(a, "1");

	int b = STo<int>(a);
	checkString(a, "1");
}

int main() {
	testConstructor();
	testAssignment();
	testInsert();
	testPop();
	testSearch();
	testSort();
	removeTests();
	testSplit();

	std::cout << "All tests passed!" << std::endl;
	return 0;
}