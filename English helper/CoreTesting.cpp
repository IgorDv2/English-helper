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
	cout<< "��� ���������� ����� �� Phrasal verbs, Prepositional phrases, Word patterns"<<endl<<"������� '1'"<<endl;
	cout << "��� ���������� ����� ������� finish"<<endl;
	cout << "��� �������� ������� ������� next" << endl;
	cin >> testingType;
	return testingType;
}

int CoreTesting::FileToArray()
{	
	ifstream DataFile;
	//string ActiveLine;
	
	int answerIndexChar = 0;
	int characterIndex = 0;
	std::string bufferString;
	
	DataFile.open("PhrasalV.txt", ios::out);

	while (getline(DataFile, bufferString)) {															//���� �� ���������� ������ � �����

		//bufferString = ActiveLine;
		characterIndex = bufferString.length();
		bufferString.copy(QuestionArr[QuestionNumber], characterIndex + 1);							//������ ������ � ������ �����������
		QuestionArr[QuestionNumber][characterIndex] = 0;											//� ����� ������� 0 -  ����� ������
		
		for (int x = 0; x < characterIndex; x++) {													//���� ��� ����������� "���� ������"
			if ((QuestionArr[QuestionNumber][x] == '\t')) {											//��������� ��������� �� ��, ��� ����� ��� ������� ��� ������ ������� �������
				QuestionArr[QuestionNumber][x] = ' ';												//������� ���������
				x++;
				answerIndexChar = 0;																//�������� ������� ���������� ������� "������"
				
				while (QuestionArr[QuestionNumber][x] != 0) {										//���� ������� ������ �� ����������
					AnswerArr[QuestionNumber][answerIndexChar] = QuestionArr[QuestionNumber][x];	//������ ������� � ������ ��� ������� �����������
					QuestionArr[QuestionNumber][x] = 0;
					x++;
					answerIndexChar++;
				}

				AnswerArr[QuestionNumber][answerIndexChar] = 0;										//������ ���� ����� ������ � ����� ������
			}
		}
		if (QuestionArr[QuestionNumber][0] != '\n' && QuestionArr[QuestionNumber][0] !=0 && QuestionArr[QuestionNumber][0]!='*')  //��� ������� ��������� ���������� ������ ������ � ������, ������������ � *
			QuestionNumber++;																		//������ ��� ���������� ����� �������, ���� ������ ��������� ������ � ������
	}
	//ActiveLine = AnswerArr[1];
	//cout << ActiveLine<<endl;
	Randomize();																					//����� ����� ��������� �������� � ��������� � �������� - ����������� ������ ��������� �����
																									//��� ��������� �������� � ��������� �������

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

int CoreTesting::PhrasalTesting()														//�������� ����� ��� ������� �����
{
	int activeQuestionNumber = 0;														//������ ��������/������ � ������� �� ���������
	string activeAnswer;																//��������� ����� ��� �������� ������������ ������
	string activeQuestion;																//��������� ����� ��� �������� �������
	int typeCommand=TestingType;																//����������� ����������
	

	for (;;) {
		activeAnswer = AnswerArr[RandomNumberArrPointer[activeQuestionNumber]];			//� ����� ���������� ������, ��������������� ����������
		activeQuestion = QuestionArr[RandomNumberArrPointer[activeQuestionNumber]];		//�����, �������� � ������� ��������� ������
		
		cout << activeQuestion <<"___"<< endl;

		if (typeCommand == 0|| activeQuestionNumber == QuestionNumber) {						//���� ����������� ������ ���� ��� �������� ���� ����� �� �����
			break;																		//���� ���� ������� �������� ��������� 0
		}

		typeCommand =checkAnswer(getAnswer(), activeAnswer);									//�������� ����������� ������
																						//��� ���������� ������ ��������� ����� ������
		if (typeCommand == 1) {
			activeQuestionNumber++;
		}

		if (typeCommand == 3) {																//� ������ �������� ������� - ��������� ���������� �����
			printColorText(AnswerArr[RandomNumberArrPointer[activeQuestionNumber]], 0, 3);				//� ����� ��������� ����� ������
			cout << endl;
			activeQuestionNumber++;
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

int CoreTesting::checkAnswer(string answer, string rightAnswer){				
//��������� ��������� ����� � ���������� 1 ��� ���������� ������,
//2 ��� ������������
//3 ��� �������� ������� "next" - ��� �������� ������� � ��������� ����������� ������ 
//� 0 ��� ������� finish
	if (answer == rightAnswer) {
		printColorText("Correct\n", 0, 3);
		return 1;
	}

	else if (answer == "finish") {
		return 0;
	}

	else if (answer == "next") {
		return 3;
	}

	else {
		printColorText("INCORRECT\n", 0, 4);
		return 2;
	}

}

int CoreTesting::Randomize()								//����� ��� ��������� ������������������ ���������
{															//��������������� �����
	int* nonReccurentCheckArr = NULL;
	int* randomNumbersArr = NULL;
	int arrlength;
	arrlength = QuestionNumber;
	nonReccurentCheckArr = new int[arrlength];									//�������� ������, ��� �����, ������� ��� ���� ������������ (����� ����� �� �����������) 
	randomNumbersArr = new int[arrlength];								//������ � �������� ������������������� ��������������� ��������� �����

	int RandBuff;											//�������� ����� ��� ���������������� �����
	int x=0;
	RandomNumberArrPointer = randomNumbersArr;												//�������� ����� ������� �������� ������� � POINT

	srand(time(NULL));

	for (int i = 0; i < QuestionNumber; i++) {							//�������� ������ ��������� �������, ������� ����� �� ����� ���� �������� �������
		nonReccurentCheckArr[i] = -1;
	}
	
	for (;;) {												//���� �������� �� ��� ���, ���� �� ����� �������������� ���������� ����� ������ ���������� �������� � �����
		RandBuff = (1 + rand() % QuestionNumber -1) ;

		if (nonReccurentCheckArr[RandBuff] == -1) {							//���� �������������������� ����� ��� �� �������������, ���������� ��� � ������
			randomNumbersArr[x] = RandBuff;
			nonReccurentCheckArr[RandBuff] = -2;
			x++;
		}

		if (x == QuestionNumber) break;

	}

	//for (int y=0; y < NUM; y++) {
	//	cout << p1[y] <<" " << p[y]<<endl;
	//}
	return 0;
}

