#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(){}

MusicPlayer::MusicPlayer(std::vector<Playlist> _playlists,User* _user): user(_user),playlists(_playlists){}
MusicPlayer::~MusicPlayer()	{}

bool MusicPlayer::Register()
{
	std::cout << "--------Register--------" << std::endl;
	std::string username;
	do 
	{
		std::cout << "> Enter a username: ";
		std::cin >> username;
		std::cin.ignore(INT_MAX, '\n');
		
	} while (!db.available_username(username));

	std::string password;
	std::cout << "> Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	std::string fullname;
	std::cout <<"> Enter a fullname: ";
	std::getline(std::cin, fullname);

	std::string birthday;
	std::cout << "> Enter your birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');
	User new_user(username,password, fullname, birthday,new_guid());
	bool success= db.add_user(new_user);
	if (success)
	{
		std::cout << "> Successfully registered " << new_user.get_username() << std::endl;
		return true;
	}
	else {
		std::cout << "> User " << user->get_username() <<" already exists!"<< std::endl;
		return false;
	}

}
bool MusicPlayer::Login()
{
	std::cout << "--------Login--------" << std::endl;
	std::string username;
	std::cout << "> Enter a username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');

	std::string password;
	std::cout << "> Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');

	if (db.login_validation(username, password)) {
		user = db.get_user_by_username(username);
		std::cout << "> Successfully logged in as " << user->get_username() << std::endl;
		return true;
	}
	std::cout << "> Login failed " << std::endl;
	return false;
}
