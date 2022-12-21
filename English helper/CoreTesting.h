#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
using namespace std;

class CoreTesting
{
public:
	char arr[200][200];
	char AnswerArr[200][200];
	int NUM = 0;
	int*  POINT;

	CoreTesting() {
		TestingType=StartTesting();

	}
	~CoreTesting(){
		EndTesting();
	}
	int StartTesting();
	int FileToArray();
	int EndTesting();
	int PhrasalTesting();
	string getAnswer();
	int checkAnswer(string , string );
	int Randomize();

protected:
	int TestingType = 0;
};

