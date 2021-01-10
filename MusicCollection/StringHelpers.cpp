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
			{
				curr_expression += ' ' + _str.substr(0, _str.size() - 1);
				break;
			}
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

/// helper function for converting string (most likely user input) to structure tm
/// 
/// @param _str - const string in format DD/MM/YYYY
/// @returns tm structure with ready to use properties: tm_year,tm_mon,tm_mday

// WORKING ONLY FOR FORMAT DD/MM/YYYY
static tm string_to_tm(const std::string _birthday)
{
	struct tm result;
	sscanf_s(_birthday.c_str(), R"(%d/%d/%d)", &result.tm_mday, &result.tm_mon, &result.tm_year);
	result.tm_year -= 1900;
	result.tm_mon -= 1;
	return result;
}

/// Beautiful print for favorite genres 
/// 
/// used only for printing in console, not in any business logic
/// @returns beautiful string containing all favorite genres
static const std::string genres_print(const std::vector<std::string> _genres)
{
	std::string s = "{ ";
	for (std::string g : _genres)
	{
		s.append(g);
		s.append(", ");
	}
	s.pop_back();
	s.pop_back();
	s.append(" }");
	if (s.size()<3)
	{
		return "{ }";
	}
	return s;
}

/// Converting tm structure to string
/// 
/// Used for saving in .json files
/// @returns string in format DD/MM/YYYY representing the birthday
static const std::string birthday_to_string(const tm& _birthday) 
{
	std::string s;
	s.append(std::to_string(_birthday.tm_mday));
	s.append("/");
	s.append(std::to_string(1 + _birthday.tm_mon));
	s.append("/");
	s.append(std::to_string(1900 + _birthday.tm_year));
	return s;
}

/// Checks if string is expression
/// <param name="_str">expression to check</param>
/// <returns>True if the string is expression containing more than one operands</returns>
static bool is_expression(std::string _str)
{
	return std::count(_str.begin(), _str.end(), ' ') != 0;
}