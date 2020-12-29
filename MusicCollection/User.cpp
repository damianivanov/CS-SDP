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

User& User::operator=(const User& other)
{
	if (this!=&other)
	{
		copy(other);
	}
	return *this;
}
void User::add_favorite_genre(std::string _genre)
{

	transform(_genre.begin(), _genre.end(), _genre.begin(), ::tolower);
	for (std::string genre: favorite_genres)
	{
		transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
		if (genre ==_genre)
		{
			return;
		}
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
		{
			favorite_genres.erase(std::remove(favorite_genres.begin(), favorite_genres.end(), _genre), favorite_genres.end());
		}
	}
}
const std::string User::birthday_to_string() const
{
	std::string s;
	s.append(std::to_string(this->birthday.tm_mday));
	s.append("/");
	s.append(std::to_string(1 + this->birthday.tm_mon));
	s.append("/");
	s.append(std::to_string(1900 + this->birthday.tm_year));
	return s;
}
std::string User::genres_print()
{
	std::string s="{ ";
	for (auto g: favorite_genres)
	{
		s.append(g);
		s.append(", ");
	}
	s.pop_back();
	s.pop_back();
	s.append(" }");
	return s;
}

//WORKING ONLY FOR FORMAT DD/MM/YYYY
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
		id = other.id;
		username = other.username;
		password = other.password;
		fullname = other.fullname;
		birthday = other.birthday;
		favorite_genres = other.favorite_genres;
		//playlists = std::vector<Playlist>(other.playlists);
	}
}

