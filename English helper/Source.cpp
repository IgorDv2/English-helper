#include<iostream>
#include<fstream>
#include"CoreTesting.h"
#include <windows.h>
#include<string>
#include <algorithm>


using namespace std;

int main() {
	SetConsoleCP(1251);				//эти две строчки нужны для отображения
	SetConsoleOutputCP(1251);		//русских букв в консоли Windows

	CoreTesting case1;
	case1.FileToArray();			//Подготавливает строчки из файла для тестирования
	case1.PhrasalTesting();			//Начинает тестирование, запрашивает тип тестирования
	

	return 0;
}