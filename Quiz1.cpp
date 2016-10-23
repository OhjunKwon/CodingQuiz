// Quiz1.cpp : Defines the entry point for the console application.
// 비주얼스튜디오로 컴파일했습니다.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	map<string, int> list;
	string name;
	int maxVote = 0;

	while (true)
	{
		getline(cin, name);
		if (name.length() == 0)
			break;
		
		list[name] = (list.find(name) == list.end()) ? 1 : list[name] + 1;
		maxVote = max(maxVote, list[name]);
	}

	for (auto const& e : list)
	{
		if (e.second < maxVote)
			continue;
		cout << e.first << endl;
	}

    return 0;
}


