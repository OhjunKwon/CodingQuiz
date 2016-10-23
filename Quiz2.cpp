// Quiz2.cpp : Defines the entry point for the console application.
// ���־�Ʃ����� �������߽��ϴ�.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>

typedef unsigned long ulong;

enum TokenTypes { OpCode, Value };

typedef struct token
{
	int type;
	ulong value;

	token() : type(OpCode), value(0) { }
	token(int t, ulong v) : type(t), value(v) { }
} Token;

using namespace std;

int calculate(string& expr)
{
	stack<Token> tokens;
	Token tk;
	ulong sum = 0;

	for (auto const& t : expr)
	{
		ulong v = 0;

		switch (t)
		{
		case '(': tokens.push(Token(OpCode, 1)); break;
		case '{': tokens.push(Token(OpCode, 2)); break;
		case '[': tokens.push(Token(OpCode, 3)); break;
		case ')': v = 1; break;
		case '}': v = 2; break;
		case ']': v = 3; break;
		case ' ': break;
		default:
			return 0;
		}

		if (v == 0)
			continue;
		if (tokens.empty())
			return 0;
		tk = tokens.top();
		tokens.pop();
		if (tk.type == OpCode)
		{
			if (tk.value != v)
				return 0;			
			tokens.push(Token(Value, v));
		}
		else
		{
			sum = tk.value;
			while (!tokens.empty())
			{
				tk = tokens.top(); tokens.pop();
				if (tk.type == OpCode)
				{
					if (tk.value != v)
						return 0;
					break;
				}
				sum += tk.value;
				sum %= 100000000;
			}
			tokens.push(Token(Value, (sum * v) % 100000000));
		}
	}

	sum = 0;
	while (!tokens.empty())
	{
		sum += tokens.top().value;
		sum %= 100000000;
		tokens.pop();
	}
	return sum;
}

int main()
{
	int count;
	cin >> count;
	if (count > 100)
		return 0;

	vector<string> inputs;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < count; i++)
	{
		string line;
		//getline, cin�� 4094 ���ڱ��� �о� �ɴϴ�.
		//���� 4094 ���ķ� �Էµ� �Է°��� 4094���� ���ڸ� ���˴ϴ�.
		getline(cin, line);
		inputs.push_back(line);
	}

	cout << endl;
	for (auto e : inputs)
		cout << calculate(e) << endl;
	
	return 0;
}

