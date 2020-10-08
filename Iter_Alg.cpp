// Iter_Alg.cpp : Defines the entry point for the console application.
//
//���������. ����������� ���������. ���������.

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

	//������� 1. ���������

	//����������� ���������. ����������� set<Point>. ���������, ���
	//����� ����������� � ������ Point. �������� ������, �������� �������� 
	//�������� ������� ��������� set, �� ����������� �� ��������
	std::set<Point> sP;
	for (size_t i = 0; i < 5; i++)
	{
		sP.insert(Point(i + 1, i * i));
	}
	std::vector<Point> vP(sP.rbegin(), sP.rend());
	stop


	//��������� ���������. � ������� ostream_iterator �������� ����������
	//vector � set �� ����������� ������� �� �����.
	std::ostream_iterator <Point> os(std::cout, " ");
	std::copy(vP.begin(), vP.end(), os);
	std::cout << '\n';
	std::copy(sP.begin(), sP.end(), os);
	stop



		//��������� �������. � ������� ������������ ���������:
		//back_inserter()
		//front_inserter()
		//inserter()
		//���������� ������� �������� �������� � ����� �� ��������� �����������. ���������:
		//����� �� ���������� ������� ����� ������������ � ������ �����������. 

	//c set'�� � list'�� ������ ������������ back_inserter() � front_inserter();
	//c �������� front_inserter()
	Point ar[] = { Point(1,2), Point(3,4), Point(20,3) };
	back_insert_iterator <std::vector<Point>> vBI = back_inserter(vP);
	std::copy(ar, ar + sizeof(ar) / sizeof(ar[0]), vBI);

	std::insert_iterator <std::set<Point>> sI = inserter(sP, sP.begin());
	std::copy(ar, ar + 2, sI);

	stop

		///////////////////////////////////////////////////////////////////

			//������� 2. ���������� ��������� (������������ ���� <algorithm>). ���������.

			// �������� for_each() - ����� �������� ������� ��� ������� �������� ����� ������������������
			//(������, vector, list...)
			//� ������� ��������� for_each � ����� ������������������ � ���������� ������ ����
			//������������ �������� ���������
			//��������� : ������� ���������� ������� ���������� ��� ������
	std::cout << '\n';
	std::for_each(vP.begin(), vP.end(), printPred<Point>);
	

	stop

	//� ������� ��������� for_each � ����� ������������������ � ���������� ���� Point
	//�������� "����������" �� ��������� �������� (����� �������� ���� ����� ����������� 
	//��� ������) � �������� ��������� � ������� ����������� ��������� 
	std::cout << '\n';
	std::vector<Point>::iterator It= vP.begin();
	++It;
	++It;		//����� ���� �����������
	++It;
	std::for_each(vP.begin(), It, Change<Point>(Point(10, 15)) );
	std::for_each(vP.begin(), vP.end(), printPred<Point>);


	//� ������� ��������� find() ������� � ����� ������������������ ��������� Point
	//��� ��������� �� ������� Point � ��������� ���������.

	std::vector<std::vector<Point>::iterator> vecIters;
	std::vector<Point>::iterator tmpIt = vP.begin();

	while ( (tmpIt = find(tmpIt, vP.end(), Point(10, 15))) != vP.end())
	{
		vecIters.push_back(tmpIt);
		tmpIt++;
	}

	stop




		//� ������� ��������� sort() ������������ ����� ������������������ ��������� Point. 
		////�� ��������� �������� ��������� ������������������ �� �����������.
		//��� ������ ���� ���������� � ������ Point?
		// ���������: ���������� �������� sort �� �������� �� �������, ��� ���
		//��� ���� �� �� ���������� => ��� ������ ���������� ����������� ������� ������!!!


		// � ������ Point ������ ���� ��������� �������� <.

	std::sort(vP.begin(), vP.end());

	stop


		//� ������� ��������� find_if() ������� � ����� ������������������ ��������� Point
		//�������� �� ������� Point, ��������������� �������: ���������� x � y ����� � ����������
		//[-n, +m].

	std::vector<Point>::iterator Iter1 = find_if(vP.begin(), vP.end(), PredXYIn(-10, 10));

	if (Iter1 != vP.end()) 
	{
		std::cout << "Founded!";
	}

	stop

		//� ������� ��������� sort() ������������ ����� ������������������ ��������� Rect,
		//���������� �������������� �� �������� ������ �� ������ ���������.

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
		//�������� �������, ������� � ������� ��������� transform ��������� 
		//���������� ������� string � ������ �������.
		//���������: ����� string - ��� "�����" ���������, ������� ��� ����
		// ���������� ������ begin() � end()

	std::string str("QWERTY");
	std::transform(str.begin(), str.end(), str.begin(), tolower);

	//��������� list ��������� string. 

	std::list<string> strlist;
	strlist.push_back("ASDLKJ");
	strlist.push_back("SDdqwqd");
	strlist.push_back("NLAKDSJ");
	strlist.push_back("SDLJQWE");
	//� ������� ��������� transform ���������� �������� "�������" set, ����������� ������ � ������ �������
	
	std::set<string> setstring;
	std::insert_iterator <std::set<string>> sStrInserter = inserter(setstring, setstring.begin());
	std::transform(strlist.begin(), strlist.end(), sStrInserter, tolowerPred);



		stop
	}
	
	{//copy_if
		//��� ������ � ���������� ���� string. 
		std::vector<std::string> vecStr;
		vecStr.push_back("ASDLKJ");
		vecStr.push_back("SDdqwqd");
		vecStr.push_back("NLAKDSJ");
		vecStr.push_back("SDLJQWE");
		vecStr.push_back("BbDLJQWE");
		vecStr.push_back("cLJQWE");
		vecStr.push_back("DDLJQWE");
		vecStr.push_back("EeeDLJQWE");
		//� ������� copy_if() ���������
		//������� ������� ������, ������������ � ����� "�" ��� "�", ����� � "�"...
		//��� ���� ������� ����� � �������� ������� ������ �� �����!
		std::ostream_iterator<std::string> osis(std::cout, "\n");
		
		std::cout << '\n';
		for (char ch = 'A'; ch <= 'Z'; ++ch)
		{
			copy_if(vecStr.begin(), vecStr.end(), osis, myStrCompare(ch));
		}


		stop

		//��� multimap, ���������� ����: "����� - ���������� ���� � ������"
		//pair<string, int>. � ������� copy_if ����������� ��� map-�: ������ -
		//� ������, ����������� ������ ���������� ����, 2-�� - ��������.
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

			//������������ multimap � map-�, ��������� ���������� ���� ����� ������
			//�������, ��������� �������� ������ ���������� �� ������.
			//��� ����� ������� ������������� ��� ������ ����? //���������� << ��� ����� ����

		std::cout << '\n';
		printConteiner(evenMonth);



	
		stop
	}

	return 0;
}

