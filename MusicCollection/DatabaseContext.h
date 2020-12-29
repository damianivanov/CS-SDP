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
	Context() { Serialization();}
	~Context() {Deserialization();}

	User* get_user_by_username(std::string _username);
	Song* get_song_by_name_and_artist(std::string _name, std::string _artist);
	Playlist* get_playlist_by_name_and_user_id(std::string _name, std::string _user_id);

	std::vector<std::string> get_all_playlists_by_cretor_id(std::string _creator_id);
	std::vector<Rating> get_ratings_by_song_id(std::string _string_id);

	std::vector<Song> get_n_ordered_songs(size_t _count);
	std::vector<Song> get_songs_by_list_of_genres(std::vector<std::string> genres);
	std::vector<Song> get_songs_except_genres(std::vector<std::string> genres);
	std::vector<Song> get_songs_by_rating(float _rating);
	std::vector<Song> get_songs_from_year(int _year);
	std::vector<Song> get_songs_before_year(int _year);
	std::vector<Song> get_songs_after_year(int _year);


	bool available_username(std::string _username);
	bool login_validation(std::string _username, std::string _password);
	bool rated_song(std::string _user_id, std::string _song_id);

	bool song_exists(Song _song);
	bool playlist_exists(Playlist _playlist);

	bool add_user(User _user);
	bool add_song(Song _song);
	bool add_playlist(Playlist _playlist);
	
	bool add_rating(std::string _user_id, std::string _song_id, float _rating);

	void Serialization();
	void Deserialization();
	std::vector<Song> get_all_songs() { return songs; }

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