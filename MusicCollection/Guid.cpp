#include <stdlib.h>
#include <time.h>
#include <string>


static std::string part(int _len) {
	std::string temp;
	for (int i = 0; i < _len; i++)
	{
		//0 - int 
		//1 - char
		int type = rand() % 2;
		if (type == 0)
		{
			int num = rand() % 9; // digits
			temp.append(std::to_string(num));
		}
		else {
			char c = rand() % 26 + 'a'; //letters
			temp.append(1,c);
		}
	}
	return temp;
}

///Custom GUID generator
/// 
///GUID Format: 8-4-4-4-12 sequences of random lower case letters and digits
/// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// std::string guid = new_guid();
/// ### Example output
/// guid = "0b3ec4de-91de-4a0c-8115-b85efdd403a0"
/// ~~~~~~~~~~~~~~~~~~~~~~~~~
///Generates len random chars (small letters or numbers) as string
static std::string new_guid() 
{
	srand((unsigned)time(NULL));
	std::string guid;
	guid.append(part(8));
	guid.append("-");
	guid.append(part(4));
	guid.append("-");
	guid.append(part(4));
	guid.append("-");
	guid.append(part(4));
	guid.append("-");
	guid.append(part(12));

	return guid;
}