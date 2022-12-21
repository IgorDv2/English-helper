#include "CoreTesting.h"
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include"colorfunctions.h"


using namespace std;



int CoreTesting::StartTesting()
{
	int testingType;
	cout<< "Для проведения теста по Phrasal verbs, Prepositional phrases, Word patterns"<<endl<<"Введите '1'"<<endl;
	cout << "Для завершения теста введите finish"<<endl;
	cout << "Для пропуска вопроса введите next" << endl;
	cin >> testingType;
	return testingType;
}

int CoreTesting::FileToArray()
{	
	ifstream DataFile;
	string ActiveLine;
	
	int AnswerIndexChar =0;
	int i = 0;
	std::string s;
	
	DataFile.open("PhrasalV.txt", ios::out);
	while (getline(DataFile, ActiveLine)) {

		s = ActiveLine;
		i = s.length();
		s.copy(arr[NUM], i + 1);
		arr[NUM][i] = 0;
		for (int x = 0; x < i; x++) {
			if ((arr[NUM][x] == '\t')) {
				arr[NUM][x] = ' ';
				x++;
				AnswerIndexChar = 0;
				while (arr[NUM][x] != 0) {
					AnswerArr[NUM][AnswerIndexChar] = arr[NUM][x];
					arr[NUM][x] = 0;
					x++;
					AnswerIndexChar++;
				}
				AnswerArr[NUM][AnswerIndexChar] = 0;
			}
		}
		if (arr[NUM][0] != '\n' && arr[NUM][0] !=0 && arr[NUM][0]!='*')
			NUM++;
	}
	//ActiveLine = AnswerArr[1];
	//cout << ActiveLine<<endl;
	Randomize();

	//for (int x = 0; x < NUM;x++) {
	//	ActiveLine = arr[POINT[x]];
	//	cout << ActiveLine;
	//	cout << endl;
	//}
	return 0;
}

	

int CoreTesting::EndTesting()
{	
	cout << TestingType;
	return 0;
}

int CoreTesting::PhrasalTesting()
{
	int i = 0;
	string Word;
	string ActiveLine;
	int type=TestingType;
	

	for (;;) {
		Word = AnswerArr[POINT[i]];
		ActiveLine = arr[POINT[i]];
		cout << ActiveLine<<"___"<< endl;
		if (type == 0||i==NUM) {
			break;
		}
		type=checkAnswer(getAnswer(),Word);
		if (type == 1) {
			i++;
		}
		if (type == 3) {
			printColorText(AnswerArr[POINT[i]], 0, 3);
			cout << endl;
			i++;
		}
	}

	return 0;
}

string CoreTesting::getAnswer()
{	
	string answer;
	cin>>answer;
	return answer;
}

int CoreTesting::checkAnswer(string check, string base){
//Принимает результат ввода и возвращает 1 при правельном ответе,
//2 при неправильном и 0 при команде finish
	if (check == base) {
		//cout << "Correct"<<endl;
		printColorText("Correct\n", 0, 3);
		return 1;
	}
	else if (check == "finish") {
		return 0;
	}
	else if (check == "next") {
		return 3;
	}
	else {
		//cout << "INCORRECT"<<endl;
		printColorText("INCORRECT\n", 0, 4);
		return 2;
	}

}

int CoreTesting::Randomize()
{
	int* p = NULL;
	int* p1 = NULL;
	int number;
	number = NUM;
	p = new int[number];
	p1 = new int[number];
	int RandBuff;
	int X=0;
	POINT = p1;

	srand(time(NULL));

	for (int i = 0; i < NUM; i++) {
		p[i] = -1;
	}
	
	//cout << NUM << endl;
	for (;;) {
		RandBuff = (1 + rand() % NUM-1) ;
		if (p[RandBuff] == -1) {
			p1[X] = RandBuff;
			p[RandBuff] = -2;
			X++;
		}
		if (X == NUM) break;
	}

	//for (int y=0; y < NUM; y++) {
	//	cout << p1[y] <<" " << p[y]<<endl;
	//}
	return 0;
}

