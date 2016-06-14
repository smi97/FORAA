// sort1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int col = 0;

template<class T>
bool compare(T a, T b)
{
	col++;
	return a < b;
}

template<class T, class Comp>
void mysort(T begin, T end, Comp comp)
{
    for (auto it = begin + 1; it != end; it++)
    {
		auto k = *it;
		auto l = it;
		while(l > begin && comp(k, *(--l)))
		{
			std::swap(*l, *(l+1));
		}
    }
}

int main()
{
	vector<int> a, b;
	for(int i = 0; i < 10; i++)
	{
		a.push_back(rand() % 100);
		b.push_back(rand() % 100);
	}
	for (auto it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	mysort(a.begin(), a.end(), compare<int>);
	cout << endl;
	for (auto it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	cout << endl << "my sort: " << col << endl;
	col = 0;

	sort(b.begin(), b.end(), compare<int>);

	for (auto it = b.begin(); it != b.end(); it++)
		cout << *it << " ";
	cout << endl << "std sort: " << col << endl;


	int sr = 0, first = 0, last = a.size(), search, ind = 0;
	cin >> search;

	while (first < last)
    {
        sr = first + (last - first) / 2;
        search <= a[sr] ? last = sr : first = sr + 1;
		ind++;
    }

    if (a[last] == search)
        cout << "found, index = " << last << endl;
    else
        cout << "not found" << endl;

	cout << endl << "Comlexity of search: " << ind << endl;

	system("pause");
	return 0;
}

