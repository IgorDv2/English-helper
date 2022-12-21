#include<iostream>
#include<fstream>
#include"CoreTesting.h"
#include <windows.h>
#include<string>
#include <algorithm>


using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CoreTesting case1;
	case1.FileToArray();
	case1.PhrasalTesting();
	

	return 0;
}