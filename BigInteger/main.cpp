#include "BigInteger.hpp"
#include <iostream>

void test1() {
	BigInteger a("123456789012345678901234567890");
	BigInteger b("987654321098765432109876543210");
	BigInteger c = a + b;
	std::cout << c << std::endl;
	//expected 1111111110111111111011111111100
}

void test2() {
	BigInteger a("99786864329834752984752984582993082028490385398475385793");
	BigInteger b("3874929234298438782394728934729384739250123014329874234797234");
	BigInteger c = a - b;
	std::cout << c << std::endl;
	//expected -387482944743410894764174418174480174616809452394447575941144
}

void test3() {
	BigInteger a("123456789012345678901234567890");
	BigInteger b("987654321098765432109876543210");
	BigInteger c = a * b;
	std::cout << c << std::endl;
	//expected 121932631137021795226185032733622923332237463801111263526900
}

void test4() {
	BigInteger a("28374791823801938184293874328534875763927652382293102389102289309821");
	BigInteger b("-98237912874923874981789781987291878347297");
	BigInteger c = a / b;
	std::cout << c << std::endl;
	//expected -2.888374863982362e+26
}

void test5() {
	BigInteger a = "12392384729837492841038197423899805430583095830459836456984024";
	a++;
	std::cout << a << std::endl;
	++a;
	std::cout << a << std::endl;
}

void test6() {
	BigInteger a = "12392384729837492841038197423899805430583095830459836456984024";
	std::cout << a-- << std::endl;
	std::cout << (--a) << std::endl;
}

void test7() {
	BigInteger a = "12392384729837492841038197423899805430583095830459836456984024";
	BigInteger b = a ^ 2;
	std::cout << b << std::endl;
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	return 0;
}