#pragma once
#include <limits>
#include "DatabaseContext.h"

class MusicPlayer
{
public:
	MusicPlayer();
	MusicPlayer(std::vector<Playlist> _playlists, User* _user);
	~MusicPlayer();
	User* get_logged_user() { return this->user; }
	bool logged() { return user!=nullptr; }
	
	bool Register(); //can't use "register"  bcs its reserved word
	bool login();
	//methods that need logged in user 
	bool creating_song();
	bool add_genre();
	bool remove_genre();
	bool rate_song();
	//modify user
	//.
	//.
	//.

private:
	User* user; //successfully logged  user
	std::vector<Playlist> playlists;
	Context db;

	
};
