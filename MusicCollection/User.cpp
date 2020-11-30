#pragma once
#include "User.h"

User::User() :username(""), password(""), fullname("")
{
	time_t now = time(0);
	localtime_s(&birthday, &now);
}
User::User(std::string _username, std::string _password, std::string _fullname, std::vector<std::string> _favorite_genres,std::vector<Playlist> _playlists,std::string _birthday)
{
	username = _username;
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	fullname = _fullname;
	favorite_genres = _favorite_genres;
	playlists = _playlists;
	birthday = string_to_tm(_birthday);
}
User& User::operator=(const User& other)
{
	if (this!=&other)
	{
		copy(other);
	}
	return *this;
	
}
User::~User() {
	favorite_genres.clear();
	playlists.clear();
}

void User::printBirthday()
{
	std::cout << birthday.tm_mday << "/" << 1 + birthday.tm_mon << "/" << 1900 + birthday.tm_year << std::endl;
}
tm User::string_to_tm(std::string birthday)
{
	struct tm result;

	sscanf_s(birthday.c_str(), R"(%d/%d/%d)", &result.tm_mday, &result.tm_mon, &result.tm_year);
	result.tm_year -= 1900;
	result.tm_mon -= 1;
	return result;
}
void User::copy(const User& other) {
	if (this != &other)
	{
		username = other.username;
		password = other.password;
		fullname = other.fullname;
		birthday = other.birthday;
		favorite_genres = other.favorite_genres;
		playlists = std::vector<Playlist>(other.playlists);
	}
}

