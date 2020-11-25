#pragma once
#include <iostream>
#include <ctime>
#include <vector>
//#include "Playlist.h"

/*Represents the basic structure 
for every user*/

class User
{
public:
	User() :username(""), password(""), fullname("")
	{ 
		time_t now = time(0);
		localtime_s(&birthday,&now);
	}
	User(std::string _username, std::string _password, std::string _fullname 
		//std::vector<std::string> _favorite_genres, std::vector<Playlist> _playlists
		) {
		username = _username;
		password = _password;
		//favorite_genres = _favorite_genres;
		//playlists = _playlists;
	}
	tm get_birthday() { return birthday; }

	~User(){}

private:
	std::string username;
	std::string password;
	std::string fullname;
	struct tm birthday;
	//std::vector<std::string> favorite_genres;
	//std::vector<Playlist> playlists;

	void copy(const User &other) {
		if (this!=&other)
		{
			username = other.username;
			password = other.password;
			fullname = other.fullname;
			birthday = other.birthday;
			//playlists = std::vector<Playlist> (other.playlists);
			//favorite_genres = other.favorite_genres;
		}
	}
	
};
