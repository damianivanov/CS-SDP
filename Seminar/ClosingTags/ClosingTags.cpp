// ClosingTags.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>

using namespace std;
bool valid(string code)
{
	stack<char> s;
	try
	{
		for (int i = 0; i < code.size(); i++)
		{
			char c = code[i];
			if (c == '<' && (code[i + 1] == 'f' || code[i + 1] == 'b' || code[i + 1] == 'm') && code[i + 2] == '>')
			{
				s.push(code[i + 1]);
				c += 2;
			}
			if (c == '<'
				&& code[i + 1] == '/'
				&& (code[i + 2] == 'f' || code[i + 2] == 'b' || code[i + 2] == 'm')
				&& code[i + 3] == '>') {

				if (s.top() == code[i + 2])
				{
					s.pop();
					c += 3;
				}
				else
					return false;
			}
		}

	}
	catch (const std::exception&)
	{

	}
	
	return s.empty();
}

int main()
{
	string valid_string = "<f>lorem<m>ipsum</m>dolor</f>";
	string invalid_string = "<f>lorem<m>ipsum</f>dolor</m>";
	string invalid_string2 = "<f>lorem<m>ipsum</m>dolor</f";

	cout << boolalpha << valid(valid_string) << endl;
	cout << boolalpha << valid(invalid_string) << endl;
	cout << boolalpha << valid(invalid_string2) << endl;


}

//<f>
//<m>
//<b>
