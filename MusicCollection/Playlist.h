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

	const std::string get_name() const { return this->name; }
	const std::vector<Song> get_songs() const { return this->songs; }
	const User* get_creator() const { return this->creator; }

	void set_creator(User* _creator) { this->creator = _creator;}
	void set_name(std::string _name) { this->name = _name; }
	void set_songs(std::vector<Song> _songs) { this->songs = _songs; }

	void add_song(Song song); // ne na 100 procent
	void print_all_songs();

private:

	User* creator;
	std::string name;
	std::vector<Song> songs;

};


