#pragma once
#include "Playlist.h"

class MusicPlayer
{
public:
	MusicPlayer();
	MusicPlayer(std::vector<Playlist> _playlists, User* _user);
	~MusicPlayer();

private:
	User* user; //successfully logged  user
	std::vector<Playlist> playlists;
		
};
