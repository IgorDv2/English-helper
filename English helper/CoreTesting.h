#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
using namespace std;

class CoreTesting
{
public:
	char arr[200][200];					//массив для хранения строк, содержащих вопросы
	char AnswerArr[200][200];			//массив для хранения правильных ответов
	int NUM = 0;						//общее число вопросов/ответов
	int*  POINT;						//Указатель на массив со случайными числами

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

protected:
	int TestingType = 0;				//хранит число, соответствующее типу тестирования
										//0-тест закончен
										//1-тест на знание фразовых конструкций
};

