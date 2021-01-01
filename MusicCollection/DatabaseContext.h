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

	/// Deserialization() method is called when Context is created
	/// with Deserialization() - songs,playlists,ratings,users are loaded and converted to ready to use vectors from json files
	Context() {Deserialization();}

	/// Serialization() method is called when Context is destructed
	/// with Serialization() - songs,playlists,ratings,users are saved to json files
	~Context() {Serialization();}

	/// Get User with given username
	/// 
	/// <param name="_username">searched username</param>
	/// <returns>pointer to the User with this username, and nullptr if there is not such User</returns>
	User* get_user_by_username(std::string _username);

	/// Get Song with given name and artist name
	/// 
	/// <param name="_name">searched Song name</param>
	/// <param name="_artist">artist name</param>
	/// <returns>pointer to the Song with this name and artist, and nullptr if there is not such Song</returns>
	Song* get_song_by_name_and_artist(std::string _name, std::string _artist);

	/// Get Playlist by given name and user id
	/// 
	/// <param name="_name"> playlists name</param>
	/// <param name="_user_id">creator id</param>
	/// <returns>Pointer to the playlist, nullptr if the pointer doesn't exist</returns>
	Playlist* get_playlist_by_name_and_user_id(std::string _name, std::string _user_id);

	/// All playlists by creators id
	/// <param name="_creator_id">Creators id</param>
	/// <returns>vector of playlists names</returns>
	std::vector<std::string> get_all_playlists_by_cretor_id(std::string _creator_id);

	/// All ratngs for a given song
	/// <param name="_song_id">Song id</param>
	/// <returns>vector of Rating</returns>
	std::vector<Rating> get_ratings_by_song_id(std::string _song_id);

	/// All songs in the database
	/// <returns>vector of Song</returns>
	std::vector<Song> get_all_songs() { return songs; }

	/// First n songs ordered by name ascending order
	/// <param name="_count">how many songs to get returned</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> get_n_ordered_songs(size_t _count);

	/// All songs with genre in the given list of genres 
	/// <param name="_genres">list of genres</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> get_songs_by_list_of_genres(std::vector<std::string> _genres);

	/// All songs with genre that are not in the given list of genres 
	/// <param name="_genres">lsit of genres</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> get_songs_except_genres(std::vector<std::string> _genres);

	/// All songs with rating more than _rating
	/// <param name="_rating">given rating</param>
	/// <returns>vector Song</returns>
	std::vector<Song> get_songs_by_rating(float _rating);
 
	/// All songs with realease year equal than _year
	/// <param name="_year">year</param>
	/// <returns>vector Song</returns>
	std::vector<Song> get_songs_from_year(int _year);

	/// All songs with realease year less than _year
	/// <param name="_year">year</param>
	/// <returns>vector Song</returns>
	std::vector<Song> get_songs_before_year(int _year);

	/// All songs with realease year more than _year
	/// <param name="_year">year</param>
	/// <returns>vector Song</returns>
	std::vector<Song> get_songs_after_year(int _year);


	/// Check if _username is available
	/// <param name="_username">given username</param>
	/// <returns>True if the username is available, False if its not </returns>
	bool available_username(std::string _username);

	/// Checks if there is user with this username and this password
	/// <param name="_username">username</param>
	/// <param name="_password">password</param>
	/// <returns>True if its valid login,False if there is no user with this username or the password is wrong </returns>
	bool login_validation(std::string _username, std::string _password);

	/// Checks if user is already voted for particular song
	/// <param name="_user_id">User id</param>
	/// <param name="_song_id">Song id</param>
	/// <returns>True if song is already voted for, False if its not </returns>
	bool rated_song(std::string _user_id, std::string _song_id);

	/// Checks if there is already song with this information
	/// Checks if the name,artist,album,genre are the same as any song in the database
	/// <param name="_song">Song to get compared to </param>
	/// <returns>True if there is song with this information, False if there is not</returns>
	bool song_exists(Song _song);

	/// Check if there is existing playlist with the same name by the same creator
	/// <param name="_playlist">Playlist to get compared to</param>
	/// <returns>True if there is playlist with the same name and creator,False if there is not</returns>
	bool playlist_exists(Playlist _playlist);

	/// Adds User to the database
	/// If available_username() returns true which means there is not a User with the same username
	/// this function add _user to the database and return true, else returns false
	bool add_user(User _user);

	/// Adds Song to the database
	/// If song_exists(_song) returns true which means there is a Song with the same name,artist,album and genre
	/// this function dont add _song to the database and return false, else returns true and adds _song 
	bool add_song(Song _song);

	/// Adds user to the database
	/// If playlist_exists(_playlist) returns true which means there is a Playlist with the same name and creator
	/// this function dont add _playlist to the database and returns false, else returns true and adds _playlist 
	bool add_playlist(Playlist _playlist);
	
	/// Bussines logic behind adding rating
	/// uses rated_song() to determine if there is already vote for _song by _user
	/// <param name="_user_id">User id</param>
	/// <param name="_song_id">Song id</param>
	/// <param name="_rating">Rating value</param>
	/// <returns>True if the adding is successful,else if its not</returns>
	bool add_rating(std::string _user_id, std::string _song_id, float _rating);

	/// The logic behind converting json files to objects
	/// 
	/// for that there has to be methods 
	/// - from_json() - tells the json library how to convert json to specific class type
	/// then the conversation is as easy as:
	/// ~~~~~~~~~~~~~~~~~.cpp
	/// std::string s; - json fortmated string
	/// json json = json::parse(s);
	/// std::vector<Type> v = json.get<std::vector<Type>>(); - vector of objects  
	/// ~~~~~~~~~~~~~~~~~
	void Serialization();

	/// The logic behind converting objects to json files 
	/// 
	/// for that there has to be methods 
	/// - to_json() - tells the json library how to convert object of specific type to json
	/// then the conversation is as easy as:
	/// ~~~~~~~~~~~~~~~~~.cpp
	/// std::ofstream out("Filename.json");
	/// json json = std::vector<Type>();
	/// out << json.dump(formating_spaces); - formated json file of objects
	/// ~~~~~~~~~~~~~~~~~
	void Deserialization();

private:
	/// number of spaces in the beggining of every line in the .json files
	const unsigned int formating_spaces = 4;
	
	const std::string users_address = "Users.json";
	const std::string playlists_address = "Songs.json";
	const std::string songs_address = "Playlists.json";
	const std::string ratings_address = "Ratings.json";

	/// Json object which reads and writes in json format
	json json;

	/// vector of all users in the database
	std::vector<User> users;

	/// vector of all playlists in the database
	std::vector<Playlist> playlists;

	/// vector of all songs in the database
	std::vector<Song> songs;

	/// vector of all ratings in the database
	std::vector<Rating> ratings;

};