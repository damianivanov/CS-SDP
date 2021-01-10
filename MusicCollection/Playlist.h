#pragma once
#include "User.h"
#include "Song.h"
class User;

class Playlist
{
public:

	Playlist();
	~Playlist();

	/// Operator==
	/// 
	/// Two Playlists are the same if the creators id and the name are the same
	/// <param name="other"> object to get compared to</param>
	/// <returns>True or False</returns>
	bool operator== (const Playlist& other) { return name == other.name && creator_id == other.creator_id; }

	/// Get Name
	/// 
	/// <returns>Playlists name</returns>
	const std::string get_name() const { return this->name; }

	/// Get Songs
	/// 
	/// <returns>vector of Songs</returns>
	const std::vector<Song> get_songs() const { return this->songs; }

	/// Get Creator Id
	/// 
	/// <returns>Creators id</returns>
	const std::string get_creator_id() const { return this->creator_id; }

	/// Set Creator
	/// 
	/// <param name="_creator_id">creator id</param>
	void set_creator(const std::string _creator_id) { this->creator_id = _creator_id;}

	/// Set Name
	/// 
	/// <param name="_name">Name of the playlist</param>
	void set_name(const std::string _name) { this->name = _name; }

	/// Set the songs of the playlist
	/// 
	/// <param name="_songs">vector of Songs</param>
	void set_songs(const std::vector<Song> _songs) {this->songs = _songs; }

	/// Simple print function 
	/// 
	/// Calls the print function of every Song in the playlist
	void print_all_songs();
private:

	/// Unique creator id
	/// 
	/// GUID - the id of User
	std::string creator_id;

	/// Name
	/// 
	/// Name of the playlist
	std::string name;

	/// Songs
	/// 
	/// All of the songs in the playlist
	std::vector<Song> songs;

};