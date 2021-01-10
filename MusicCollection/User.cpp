#pragma once
#include "User.h"

User::User() :username(""), password(""), fullname(""),id("") 
{
	time_t now = time(0);
	localtime_s(&birthday, &now);
}
User::~User() {}
User::User(std::string _username, 
		std::string _password, 
		std::string _fullname, 
		std::string _birthday,
		std::string _id,
		std::vector<std::string> _favorite_genres
)
{
	username = _username;
	password = _password;
	fullname = _fullname;
	favorite_genres = _favorite_genres;
	birthday = string_to_tm(_birthday);
	id = _id;
}

void User::add_favorite_genre(std::string _genre)
{
	transform(_genre.begin(), _genre.end(), _genre.begin(), ::tolower);

	for (std::string genre: favorite_genres)
	{
		transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
		if (genre ==_genre)
			return;
	}
	favorite_genres.push_back(_genre);
}
void User::remove_favorite_genre(std::string _genre)
{
	transform(_genre.begin(), _genre.end(), _genre.begin(), ::tolower);
	for (std::string genre : favorite_genres)
	{
		transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
		if (genre == _genre)
			favorite_genres.erase(std::remove(favorite_genres.begin(), favorite_genres.end(), _genre), favorite_genres.end());
	}
}
void User::print_user()
{
	std::cout << "Username: " << username << std::endl;
	std::cout << "Fullname: " << fullname << std::endl;
	std::cout << "Favorite genres: " << genres_print(favorite_genres) << std::endl;
	std::cout << "Birthday: " << birthday_to_string(birthday) << std::endl;
	std::cout << "Id: " << id << std::endl;
}