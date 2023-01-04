#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
using namespace std;

class CoreTesting
{
public:
	
	char QuestionArr[300][100];							//массив для хранения строк, содержащих вопросы
	char AnswerArr[300][100];							//массив для хранения правильных ответов
	int QuestionNumber = 0;								//общее число вопросов/ответов
	int*  RandomNumberArrPointer;						//Указатель на массив со случайными числами
	int ErrorsNumber = 0;								//общее количество ошибок 
	int WrongAnswer[300];								//массив для хранения номеров вопросов/ответов, где была ошибка
	int MissedQuestions[300];							//массив для номеров вопросов которые были пропущены
	int WrongIndex = 0;									//индекс массива вопросов/ответов c ошибками
	int MissedIndex = 0;								//индекс массива пропущенных впросов

	CoreTesting() {
		TestingType=StartTesting();		//Вызывается метод для определения типа теста

	}
	~CoreTesting(){
		EndTesting();
	}
	int StartTesting();					//Метод, запрашивающий тип тестирования
	int FileToArray();					//Метод, считывающий из файла строки с фразовыми конструкциями
	int EndTesting();
	int PhrasalTesting();				//запускает тестирование на знание фразовых выражений
	string getAnswer();					//считывает ответ с клавиатуры
	int checkAnswer(string , string );  //сверяет предполагаемый ответ с исходным
	int Randomize();					//Создает массив случайных, не повторяющихся целых чисел, для случайного выведения вопросов на экран	
	int TestingSummery();

protected:
	int TestingType = 0;				//хранит число, соответствующее типу тестирования
										//0-тест закончен
										//1-тест на знание фразовых конструкций
};

