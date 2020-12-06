#pragma once
#include "User.h"
using json = nlohmann::json;
User::User() :username(""), password(""), fullname("")
{
	time_t now = time(0);
	localtime_s(&birthday, &now);
	id = new_guid();
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
	id = new_guid();
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

void User::add_playlist(Playlist _playlist)
{
	for (auto playlist: playlists)
	{
		if ((playlist.get_name() == _playlist.get_name())&&(playlist.get_creator()->get_username()==_playlist.get_creator()->get_username()))
		{
			std::cout << "Already existing playlist " << _playlist.get_name() << std::endl;
			return;
		}
	}
	playlists.push_back(_playlist);
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
		username = other.username;
		password = other.password;
		fullname = other.fullname;
		birthday = other.birthday;
		favorite_genres = other.favorite_genres;
		playlists = std::vector<Playlist>(other.playlists);
	}
}

void to_json(json& j, const User& u) {
	j = json {
		{"username", u.get_username()}, 
		{"password", u.get_password()},
		{"fullname", u.get_fullname()},
		{"birthday", u.birthday_to_string()},
		{"favorite genres", u.get_favorite_genres()},
		//{"Playlist", u.get_playlists()} need to_json, from_json
	};
}
void from_json(const json& j, User& p) {
	p.set_username(j.at("username"));
	p.set_password(j.at("password"));
	p.set_fullname(j.at("fullname"));
	p.set_birthday(j.at("birthday"));
	p.set_favorite_genres(j.at("favorite genres"));



}
