#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :user(nullptr){}

MusicPlayer::MusicPlayer(std::vector<Playlist> _playlists,User* _user): user(_user),playlists(_playlists){}
MusicPlayer::~MusicPlayer()
{
	delete user;
}

bool MusicPlayer::Register()
{
	//user by reference
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k = 14;
	SetConsoleTextAttribute(hConsole, k);
	std::string username;
	do
	{
		std::cout << "Enter a username: ";
		std::cin >> username;
		std::cin.ignore(1,'\n');
		std::cin.clear();
	} while (!db.available_username(username));

	std::string password;
	std::cout << "Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	std::string fullname;
	std::cout <<"Enter a fullname: ";
	std::getline(std::cin, fullname);

	std::string birthday;
	std::cout << "Enter your birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(1,'\n');
	std::cin.clear();
	User new_user(username, password, fullname, birthday);
	return db.add_user(new_user);
	SetConsoleTextAttribute(hConsole, 15);

}
