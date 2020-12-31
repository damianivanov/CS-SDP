#include "Repl.h"

Repl::Repl() { mp = new MusicPlayer(); }
Repl::~Repl() { delete mp; }

void Repl::run()
{
	std::cout << "--------Welcome to SpotiFly--------" << std::endl;
	std::cout << "Enter a command or type \"help\" to see all supported commands " << std::endl;
	while (true)
	{
		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input == "help")
			help();
		else if (input == "exit")
			break;
		else if (input == "login")
			mp->login();
		else if (input == "register")
			mp->Register();
		else if (input == "logout")
			mp->logout();
		else if (input == "change username")
			mp->change_username();
		else if (input == "user info")
			mp->user_info();
		else if (input == "change password")
			mp->change_password();
		else if (input == "change fullname")
			mp->change_fullname();
		else if (input == "change birthday")
			mp->change_birthday();
		else if (input == "add favorite")
			mp->add_favorite_genre();
		else if (input == "remove favorite")
			mp->remove_favorite_genre();
		else if (input == "add song")
			mp->create_song();
		else if (input == "rate song")
			mp->rate_song();
		else if (input == "generate playlist")
			mp->generating_playlist();
		else if (input == "save playlist")
			mp->save_playlist();
		else if (input == "load playlist")
			mp->load_playlist();
		else if (input == "print playlist")
			mp->print_playlist();
		else if (input == "my playlists")
			mp->my_playlists();
		else
			std::cout << input << " - is not recognized as valid command" << std::endl;	
	}
}

void Repl::help()
{
	std::cout << "The following commands are supported:" << std::endl;
	std::cout << "	- help --- prints all of the supported functions" << std::endl;
	std::cout << "	- exit --- exists the program" << std::endl;
	std::cout << "	- login --- login with existing user by username and password" << std::endl;
	std::cout << "	- register --- register new user" << std::endl;
	std::cout << "Functionality for logged users" << std::endl;
	std::cout << "	- logout --- logout only if you are already logged in" << std::endl;
	std::cout << "	- user info --- prints information for the logged user" << std::endl;
	std::cout << "	- change username --- changes current user username" << std::endl;
	std::cout << "	- change password --- changes current user password" << std::endl;
	std::cout << "	- change fullname --- changes current user fullname" << std::endl;
	std::cout << "	- change birthday --- changes current uesr birthday" << std::endl;
	std::cout << "	- add favorite --- adds genre to favorite genres" << std::endl;
	std::cout << "	- remove favorite --- removes genre from favorite genres" << std::endl;
	std::cout << "	- add song --- adds new song" << std::endl;
	std::cout << "	- rate song --- rates song from 0.00 to 6.00" << std::endl;
	std::cout << "	- generate playlist --- generate playlist by multiple criterias" << std::endl;
	std::cout << "	- save playlist --- saves the current playlist" << std::endl;
	std::cout << "	- load playlist --- loads playlist from the database" << std::endl;
	std::cout << "	- print playlist --- prints info for every song in the playlist" << std::endl;
	std::cout << "	- my playlists --- prints info for every playlist created from the logged user" << std::endl;
}
