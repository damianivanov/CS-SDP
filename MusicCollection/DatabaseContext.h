#pragma once
#include <fstream>
#include "Playlist.h"
#include "Rating.h"
#include "sha3.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Context
{
public:
	//User get_user_by_id(std::string _id);
	User* get_user_by_username(std::string _username);
	Song* get_song_by_name_and_artist(std::string _name, std::string _artist);
	std::vector<Rating> get_ratings_by_song_id(std::string _string_id);


	std::vector<User> get_all_users() { return users; }
	std::vector<Playlist> get_all_playlists() { return playlists; }
	std::vector<Song> get_all_songs() { return songs; }


	bool available_username(std::string _username);
	bool login_validation(std::string _username, std::string _password);
	bool rated_song(std::string _user_id, std::string _song_id);
	bool song_exists(Song _song);

	bool add_user(User _user);
	
	bool add_rating(std::string _user_id, std::string _song_id, float _rating);
	bool add_song(Song _song);

	//maybe
	Context() {
		Serialization();
	}
	~Context() {
		Deserialization();
	}

	void Serialization();
	void Deserialization();

private:

	const std::string users_address = "Users.json";
	const std::string playlists_address = "Songs.json";
	const std::string songs_address = "Playlists.json";
	const std::string ratings_address = "Ratings.json";

	json json;
	std::vector<User> users;
	std::vector<Playlist> playlists;
	std::vector<Song> songs;
	std::vector<Rating> ratings;

	const unsigned int formating_spaces = 4;
};