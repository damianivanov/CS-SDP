#include <stdlib.h>
#include <time.h>
#include <string>

//GUID Format - 8-4-4-4-12  

//Generates 4 random chars(small letters or numbers) as string
static std::string part(int len) {
	std::string temp;
	for (int i = 0; i < len; i++)
	{
		//0 - int 
		//1 - char
		int type = rand() % 2;
		if (type == 0)
		{
			int num = rand() % 9;
			temp.append(std::to_string(num));
		}
		else {
			char c = rand() % 26 + 'a';
			temp.append(1,c);
		}
	}
	return temp;
}

static std::string new_guid() {
	srand(time(NULL));
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
