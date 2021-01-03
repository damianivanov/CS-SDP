#pragma once
#include <sstream>
#include <string>

/// Gets the next token 
/// 
/// Gets the next token from stringstream _s and saves it in _str
/// <param name="_s">stringstream by reference</param>
/// <param name="_str">string by reference</param>
/// <returns>True if there is next token, False if there is not</returns>
static bool get_next_token(std::stringstream& _s, std::string& _str)
{
	_str = "";
	std::getline(_s, _str, ' ');
	if (_str[0] == '(')
	{
		std::string curr_expression = _str.substr(1, _str.size() - 1);
		while (std::getline(_s, _str, ' '))
		{
			if (_str[_str.size() - 1] == ')')
				curr_expression += ' ' + _str.substr(0, _str.size() - 1);
			else
				curr_expression += ' ' + _str;
		}
		_str = curr_expression;
		return true;

	}
	return _str != "";
}

/// Clears leading and trailing white spaces
/// 
/// <param name="_str">string before clearing by reference</param>
static void clear_whitespaces(std::string& _str)
{
	while (!_str.empty() && std::isspace(*_str.begin()))
		_str.erase(_str.begin());

	while (!_str.empty() && std::isspace(*_str.rbegin()))
		_str.erase(_str.length() - 1);
}