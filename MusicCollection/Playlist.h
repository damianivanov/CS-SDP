#pragma once
#include "User.h"
#include "Song.h"

/*Class representing the structure of 
every playlist, containting reference to the creator 
and all of the songs
*/
class User;

class Playlist
{
public:

	Playlist();
	~Playlist();

	const std::string get_name() const { return this->name; }
	const std::vector<Song> get_songs() const { return this->songs; }
	const std::string get_creator() const { return this->creator_id; }

	void set_creator(std::string _creator_id) { this->creator_id = _creator_id;}
	void set_name(std::string _name) { this->name = _name; }
	void set_songs(std::vector<Song> _songs) { this->songs = _songs; }

	void add_song(Song song); // ne na 100 procent
	void print_all_songs();

private:

	std::string creator_id;
	std::string name;
	std::vector<Song> songs;

};


