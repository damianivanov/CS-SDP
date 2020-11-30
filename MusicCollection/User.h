#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include "sha3.h"
#include "Playlist.h"

class Playlist;
/*Represents the basic structure
for every user*/
class User
{
public:
	User();
	User(std::string _username, std::string _password, std::string _fullname, std::vector<std::string> _favorite_genres, std::vector<Playlist> _playlists, std::string _birthday);
	User& operator=(const User& other);
	~User();

	//getters

	const tm get_birthday() const { return this->birthday; } //idk about the first const 
	const std::string get_username() const { return this->username; }
	const std::string get_password() const { return this->password; }
	const std::string get_fullname() const { return this->fullname; }
	const std::vector<std::string>& get_favorite_genres() const { return this->favorite_genres; } //idk about the consts
	const std::vector<Playlist>& get_playlists() const { return this->playlists; }

	//setters

	void set_username(std::string _username) { this->username = _username; }
	void set_password(std::string _password) { this->password = _password; }
	void set_fullname(std::string _fullname) { this->fullname = _fullname; }
	void set_favorite_genres(std::vector<std::string> _favorite_genres) { this->favorite_genres = _favorite_genres; }
	void set_playlists(std::vector<Playlist> _playlists) { this->playlists = _playlists; }
	void set_birthday(tm _birthday) { this->birthday = _birthday; } //maybe out of scope 
	void set_birthday(std::string _birthday) { this->birthday = string_to_tm(_birthday); } //maybe out of scope 

	void printBirthday();

private:
	std::string username;
	std::string password;
	std::string fullname;
	tm birthday;
	std::vector<std::string> favorite_genres;
	std::vector<Playlist> playlists;
	tm string_to_tm(std::string);
	void copy(const User& other);
};
