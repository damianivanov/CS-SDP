#pragma once
#include <limits>
#include "DatabaseContext.h"

class MusicPlayer
{
public:
	MusicPlayer();
	MusicPlayer(std::vector<Playlist> _playlists, User _user);
	~MusicPlayer();
	User* get_logged_user() { return &this->user; }
	bool Register();
	bool Login();
private:
	User user; //successfully logged  user
	std::vector<Playlist> playlists;
	Context db;

	
};
