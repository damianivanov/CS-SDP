#pragma once
#include "User.h"
#include "Song.h"

/*Class representing the structure of 
every playlist, containting reference to the creator 
and all of the songs
*/
class User;
class Song;

class Playlist
{
public:

	Playlist();
	~Playlist();

private:
	User* creator;
	std::vector<const Song*> songs;

};


