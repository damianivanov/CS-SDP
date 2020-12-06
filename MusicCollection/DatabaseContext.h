#pragma once
#include "Playlist.h"

class Context
{
public:
	Context() {}
	~Context() {}

private:

	const std::string users_address = "Users.json";
	const std::string playlists_address = "Songs.json";
	const std::string songs_address = "Playlists.json";

	std::vector<User> users;
	std::vector<Playlist> playlists;
	std::vector<Song> songs;

};
