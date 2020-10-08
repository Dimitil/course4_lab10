// Iter_Alg.cpp : Defines the entry point for the console application.
//
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <tchar.h>
#include "Point.h"
#include <iterator>
#include "Rect.h"
#include "Predicats.h"

using namespace std;	
#define	  stop __asm nop




int _tmain(int argc, _TCHAR* argv[])
{
	
///////////////////////////////////////////////////////////////////

	//Задание 1. Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
	//являются копиями элементов set, но упорядочены по убыванию
	std::set<Point> sP;
	for (size_t i = 0; i < 5; i++)
	{
		sP.insert(Point(i + 1, i * i));
	}
	std::vector<Point> vP(sP.rbegin(), sP.rend());
	stop


	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.
	std::ostream_iterator <Point> os(std::cout, " ");
	std::copy(vP.begin(), vP.end(), os);
	std::cout << '\n';
	std::copy(sP.begin(), sP.end(), os);
	stop



		//Итераторы вставки. С помощью возвращаемых функциями:
		//back_inserter()
		//front_inserter()
		//inserter()
		//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
		//какие из итераторов вставки можно использовать с каждым контейнером. 

	//c set'ом и list'ом нельзя использовать back_inserter() и front_inserter();
	//c вектором front_inserter()
	Point ar[] = { Point(1,2), Point(3,4), Point(20,3) };
	back_insert_iterator <std::vector<Point>> vBI = back_inserter(vP);
	std::copy(ar, ar + sizeof(ar) / sizeof(ar[0]), vBI);

	std::insert_iterator <std::set<Point>> sI = inserter(sP, sP.begin());
	std::copy(ar, ar + 2, sI);

	stop

		///////////////////////////////////////////////////////////////////

			//Задание 2. Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

			// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
			//(массив, vector, list...)
			//С помощью алгоритма for_each в любой последовательности с элементами любого типа
			//распечатайте значения элементов
			//Подсказка : неплохо вызываемую функцию определить как шаблон
	std::cout << '\n';
	std::for_each(vP.begin(), vP.end(), printPred<Point>);
	

	stop

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката 
	std::cout << '\n';
	std::vector<Point>::iterator It= vP.begin();
	++It;
	++It;		//метод есть специальный
	++It;
	std::for_each(vP.begin(), It, Change<Point>(Point(10, 15)) );
	std::for_each(vP.begin(), vP.end(), printPred<Point>);


	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.

	std::vector<std::vector<Point>::iterator> vecIters;
	std::vector<Point>::iterator tmpIt = vP.begin();

	while ( (tmpIt = find(tmpIt, vP.end(), Point(10, 15))) != vP.end())
	{
		vecIters.push_back(tmpIt);
		tmpIt++;
	}

	stop




		//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
		////По умолчанию алгоритм сортирует последовательность по возрастанию.
		//Что должно быть определено в классе Point?
		// Замечание: обобщенный алгоритм sort не работает со списком, так как
		//это было бы не эффективно => для списка сортировка реализована методом класса!!!


		// в классе Point должен быть определен оператор <.

	std::sort(vP.begin(), vP.end());

	stop


		//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
		//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
		//[-n, +m].

	std::vector<Point>::iterator Iter1 = find_if(vP.begin(), vP.end(), PredXYIn(-10, 10));

	if (Iter1 != vP.end()) 
	{
		std::cout << "Founded!";
	}

	stop

		//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
		//располагая прямоугольники по удалению центра от начала координат.

	std::vector<Rect> vR;
	
	vR.push_back(Rect(100, 120, 14, 13));
	vR.push_back(Rect(10, 15, 14, 13));
	vR.push_back(Rect(50, 32, 14, 13));
	vR.push_back(Rect(10, 20, 14, 13));
	vR.push_back(Rect(1, 2, 14, 13));
	vR.push_back(Rect(1, 1, 14, 13));
	

	std::sort( vR.begin(), vR.end(), PredRectDistFromXY(0,0) );

	stop


	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит 
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()

	std::string str("QWERTY");
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	//Заполните list объектами string. 

	std::list<string> strlist;
	strlist.push_back("ASDLKJ");
	strlist.push_back("SDdqwqd");
	strlist.push_back("NLAKDSJ");
	strlist.push_back("SDLJQWE");
	//С помощью алгоритма transform сформируте значения "пустого" set, конвертируя строки в нижний регистр
	
	std::set<string> setstring;
	std::insert_iterator <std::set<string>> sStrInserter = inserter(setstring, setstring.begin());
	std::transform(strlist.begin(), strlist.end(), sStrInserter, tolowerPred);



		stop
	}
	
	{//copy_if
		//Дан вектор с элементами типа string. 
		std::vector<std::string> vecStr;
		vecStr.push_back("ASDLKJ");
		vecStr.push_back("SDdqwqd");
		vecStr.push_back("NLAKDSJ");
		vecStr.push_back("SDLJQWE");
		vecStr.push_back("BbDLJQWE");
		vecStr.push_back("cLJQWE");
		vecStr.push_back("DDLJQWE");
		vecStr.push_back("EeeDLJQWE");
		//С помощью copy_if() требуется
		//вывести сначала строки, начинающиеся с буквы "А" или "а", затем с "Б"...
		//При этом порядок строк в исходном векторе менять не нужно!
		std::ostream_iterator<std::string> osis(std::cout, "\n");
		
		std::cout << '\n';
		for (char ch = 'A'; ch <= 'Z'; ++ch)
		{
			copy_if(vecStr.begin(), vecStr.end(), osis, myStrCompare(ch));
		}


		stop

		//Дан multimap, содержаций пары: "месяц - количество денй в месяце"
		//pair<string, int>. С помощью copy_if сформируйте ДВА map-а: первый -
		//с парами, содержащими четное количество дней, 2-ой - нечетное.
		std::multimap<string, int> month {
			{"January", 31}, {"February", 28}, {"February", 29}, { "March", 31},
			{"April", 30}, {"May",31}, {"June", 30}, {"July", 31}, {"August",31},
			{"September",30}, {"October", 31}, {"November",30}, {"December",31}
		};

		std::map<string, int> evenMonth;
		std::insert_iterator <std::map<string, int>> mapInserter = inserter(evenMonth, evenMonth.begin());
		std::copy_if(month.begin(), month.end(), mapInserter, EvenMonthPred);

		std::map<string, int> notEvenMonth;
		mapInserter = inserter(notEvenMonth, notEvenMonth.begin());
		std::copy_if(month.begin(), month.end(), mapInserter, notEvenMonthPred); 


		stop

			//Распечатайте multimap и map-ы, используя написанный вами ранее шаблон
			//функции, выводящей элементы ЛЮБОГО контейнера на печать.
			//Что нужно сделать дополнительно для вывода пары? //перегрузил << для любой пары

		std::cout << '\n';
		printConteiner(evenMonth);



	
		stop
	}

	return 0;
}

