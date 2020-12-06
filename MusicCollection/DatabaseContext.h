#pragma once
#include <fstream>
#include "Playlist.h"
#include "sha3.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
class Context
{
public:
	User& get_user_by_id(std::string _id);
	User& get_user_by_username(std::string _username);

	std::vector<User> get_all_users() { return users; }
	std::vector<Playlist> get_all_playlists() { return playlists; }
	std::vector<Song> get_all_songs() { return songs; }


	Context() {}
	~Context() {}
	void Serialization();	
	void Deserialization();			

private:

	const std::string users_address = "Users.json";
	const std::string playlists_address = "Songs.json";
	const std::string songs_address = "Playlists.json";
	json json;
	std::vector<User> users;
	std::vector<Playlist> playlists;
	std::vector<Song> songs;
	const unsigned int formating_spaces = 4;
	bool validate_user(std::string _username, std::string _password);
};
