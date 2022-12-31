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
	//string ActiveLine;
	
	int answerIndexChar = 0;
	int characterIndex = 0;
	std::string bufferString;
	
	DataFile.open("PhrasalV.txt", ios::out);

	while (getline(DataFile, bufferString)) {															//пока не закончатся строки в файле

		//bufferString = ActiveLine;
		characterIndex = bufferString.length();
		bufferString.copy(QuestionArr[QuestionNumber], characterIndex + 1);							//кладем строку в массив посимвольно
		QuestionArr[QuestionNumber][characterIndex] = 0;											//в конце массива 0 -  конец строки
		
		for (int x = 0; x < characterIndex; x++) {													//цикл для определения "зоны ответа"
			if ((QuestionArr[QuestionNumber][x] == '\t')) {											//табуляция указывает на то, что после нее искомый для данной строчки предлог
				QuestionArr[QuestionNumber][x] = ' ';												//убераем табуляцию
				x++;
				answerIndexChar = 0;																//обнуляем счетчик начального символа "ответа"
				
				while (QuestionArr[QuestionNumber][x] != 0) {										//пока текущая строка не закончится
					AnswerArr[QuestionNumber][answerIndexChar] = QuestionArr[QuestionNumber][x];	//кладем предлог в массив для ответов посимвольно
					QuestionArr[QuestionNumber][x] = 0;
					x++;
					answerIndexChar++;
				}

				AnswerArr[QuestionNumber][answerIndexChar] = 0;										//ставим знак конца строки в конце ответа
			}
		}
		if (QuestionArr[QuestionNumber][0] != '\n' && QuestionArr[QuestionNumber][0] !=0 && QuestionArr[QuestionNumber][0]!='*')  //это условие позволяет пропускать пустые строки и строки, начинающиеся с *
			QuestionNumber++;																		//только при соблюдения этого условия, идет запись следующей строки в массив
	}
	//ActiveLine = AnswerArr[1];
	//cout << ActiveLine<<endl;
	Randomize();																					//сразу после созданияя массивов с вопросами и ответами - формируется массив случайных чисел
																									//для выведения вопросов в случайном порядке

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

int CoreTesting::PhrasalTesting()														//основной метод для запуска теста
{
	int activeQuestionNumber = 0;														//индекс вопросса/ответа в порядке их выведения
	string activeAnswer;																//строковый буфер для проверки правильности ответа
	string activeQuestion;																//строковый буфер для текущего вопроса
	int typeCommand=TestingType;																//управляющая переменная
	

	for (;;) {
		activeAnswer = AnswerArr[RandomNumberArrPointer[activeQuestionNumber]];			//в буфер помещаются строки, соответствующие случайному
		activeQuestion = QuestionArr[RandomNumberArrPointer[activeQuestionNumber]];		//числу, лежащему в массиве случайных числел
		
		cout << activeQuestion <<"___"<< endl;

		if (typeCommand == 0|| activeQuestionNumber == QuestionNumber) {						//цикл заканчивает работу либо при переборе всех строк из файла
			break;																		//либо если методом проверки возвращен 0
		}

		typeCommand =checkAnswer(getAnswer(), activeAnswer);									//проверка правильного ответа
																						//при правильном ответе выводится новая строка
		if (typeCommand == 1) {
			activeQuestionNumber++;
		}

		if (typeCommand == 3) {																//в случае пропуска вопроса - выводится правильный ответ
			printColorText(AnswerArr[RandomNumberArrPointer[activeQuestionNumber]], 0, 3);				//и после выводится новая строка
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
//Принимает результат ввода и возвращает 1 при правельном ответе,
//2 при неправильном
//3 при введении команды "next" - для пропуска вопроса и выведения правильного ответа 
//и 0 при команде finish
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

int CoreTesting::Randomize()								//метод для созданиия последовательности случайных
{															//неповторяющихся чисел
	int* nonReccurentCheckArr = NULL;
	int* randomNumbersArr = NULL;
	int arrlength;
	arrlength = QuestionNumber;
	nonReccurentCheckArr = new int[arrlength];									//буферный массив, для чисел, которые уже были использованы (чтобы чтсла не повторялись) 
	randomNumbersArr = new int[arrlength];								//массив с конечной последовательностью неповторяющихся случайных чисел

	int RandBuff;											//числовой буфер для сгенерированного числа
	int x=0;
	RandomNumberArrPointer = randomNumbersArr;												//передаем адрес первого элемента массива в POINT

	srand(time(NULL));

	for (int i = 0; i < QuestionNumber; i++) {							//буферный массив заполняем числами, которые никак не могут быть индексом массива
		nonReccurentCheckArr[i] = -1;
	}
	
	for (;;) {												//цикл работает до тех пор, пока не будет сгенерированно количество чисел равное количеству вопросов в тесте
		RandBuff = (1 + rand() % QuestionNumber -1) ;

		if (nonReccurentCheckArr[RandBuff] == -1) {							//если свежесгенерированное число еще не использованно, записываем его в массив
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

