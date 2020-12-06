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
	const std::vector<const Song*> get_songs() const { return this->songs; }
	const User* get_creator() const { return this->creator; }

	void set_creator(User* _creator) { this->creator = _creator; } //not sure if its right logic wise
	void set_name(std::string _name) { this->name = _name; }

	void add_song(const Song* song); // ne na 100 procent
private:
	std::string name;
	User* creator;
	std::vector<const Song*> songs;

};


