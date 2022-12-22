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

	while (getline(DataFile, ActiveLine)) {                        //пока не закончатся строки в файле

		s = ActiveLine;
		i = s.length();
		s.copy(arr[NUM], i + 1);									//кладем строку в массив посимвольно
		arr[NUM][i] = 0;											//в конце массива 0 -  конец строки
		
		for (int x = 0; x < i; x++) {								//цикл для определения "зоны ответа"
			if ((arr[NUM][x] == '\t')) {							//табуляция указывает на то, что после нее искомый для данной строчки предлог
				arr[NUM][x] = ' ';									//убераем табуляцию
				x++;
				AnswerIndexChar = 0;								//обнуляем счетчик начального символа "ответа"
				
				while (arr[NUM][x] != 0) {							//пока текущая строка не закончится
					AnswerArr[NUM][AnswerIndexChar] = arr[NUM][x];	//кладем предлог в массив для ответов посимвольно
					arr[NUM][x] = 0;								
					x++;
					AnswerIndexChar++;
				}

				AnswerArr[NUM][AnswerIndexChar] = 0;				//ставим знак конца строки в конце ответа
			}
		}
		if (arr[NUM][0] != '\n' && arr[NUM][0] !=0 && arr[NUM][0]!='*')  //это условие позволяет пропускать пустые строки и строки, начинающиеся с *
			NUM++;														//только при соблюдения этого условия, идет запись следующей строки в массив
	}
	//ActiveLine = AnswerArr[1];
	//cout << ActiveLine<<endl;
	Randomize();													//сразу после созданияя массивов с вопросами и ответами - формируется массив случайных чисел
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

int CoreTesting::PhrasalTesting()									//основной метод для запуска теста
{
	int i = 0;														//индекс вопросса/ответа в порядке их выведения
	string Word;													//строковый буфер для проверки правильности ответа
	string ActiveLine;												//строковый буфер для текущего вопроса
	int type=TestingType;											//управляющая переменная
	

	for (;;) {
		Word = AnswerArr[POINT[i]];									//в буфер помещаются строки, соответствующие случайному
		ActiveLine = arr[POINT[i]];									//числу, лежащему в массиве случайных числел
		
		cout << ActiveLine<<"___"<< endl;

		if (type == 0||i==NUM) {									//цикл заканчивает работу либо при переборе всех строк из файла
			break;													//либо если методом проверки возвращен 0
		}

		type=checkAnswer(getAnswer(),Word);							//проверка правильного ответа
																	//при правильном ответе выводится новая строка
		if (type == 1) {											
			i++;
		}

		if (type == 3) {											//в случае пропуска вопроса - выводится правильный ответ
			printColorText(AnswerArr[POINT[i]], 0, 3);				//и после выводится новая строка
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
//2 при неправильном
//3 при введении команды "next" - для пропуска вопроса и выведения правильного ответа 
//и 0 при команде finish
	if (check == base) {
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
		printColorText("INCORRECT\n", 0, 4);
		return 2;
	}

}

int CoreTesting::Randomize()								//метод для созданиия последовательности случайных
{															//неповторяющихся чисел
	int* p = NULL;
	int* p1 = NULL;
	int number;
	number = NUM;
	p = new int[number];									//буферный массив, для чисел, которые уже были использованы (чтобы чтсла не повторялись) 
	p1 = new int[number];									//массив с конечной последовательностью неповторяющихся случайных чисел

	int RandBuff;											//числовой буфер для сгенерированного числа
	int X=0;
	POINT = p1;												//передаем адрес первого элемента массива в POINT

	srand(time(NULL));

	for (int i = 0; i < NUM; i++) {							//буферный массив заполняем числами, которые никак не могут быть индексом массива
		p[i] = -1;
	}
	
	for (;;) {												//цикл работает до тех пор, пока не будет сгенерированно количество чисел равное количеству вопросов в тесте
		RandBuff = (1 + rand() % NUM-1) ;

		if (p[RandBuff] == -1) {							//если свежесгенерированное число еще не использованно, записываем его в массив
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

