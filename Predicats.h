#pragma once
#include <iostream>

template <typename T>
void printConteiner(const T& cont)
{
	for (typename T::const_iterator it = cont.begin(); it != cont.end(); ++it)
	{
		std::cout << *it << '\n';
	}
}

template <typename F, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<typename F, typename S>& p)
{
	out << p.first << ' ' << p.second;
	return out;
}

template<typename T>
void printPred(const T& t)
{
	std::cout << t << ' ';
}

template <typename T>
class Change {
	T _t;

public:
	Change(const T& t) : _t(t) {}
	void operator()(T& t)
	{
		t = _t;
	}
};

class myStrCompare {
	char _ch;
public:
	myStrCompare(char ch) : _ch(ch) {}
	bool operator()(const std::string& s)
	{
		if (!s.empty())
		{
			return (_ch == s[0]) || ((_ch^32) == s[0]);
		}
		return false;
	}
};

std::string tolowerPred(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), tolower);
	return s;
}

bool EvenMonthPred(const std::pair<std::string, int>& p)
{
	return !(p.second & 1);
}

bool notEvenMonthPred(const std::pair<std::string, int>& p)
{
	return (p.second & 1);
}