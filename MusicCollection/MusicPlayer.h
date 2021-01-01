#pragma once
#include <sstream>
#include <limits>
#include "DatabaseContext.h"

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();
	/// Checks if there is logged user
	/// Default value of users id is with id = ""
	/// <returns>True if there is logged user and False if there is not one</returns>
	bool logged() { return !user->get_id().empty(); }

	/// The bussines logic behind registering a new user
	/// 
	/// It can be unsuccessful if the username is taken
	/// <returns>True if the registration is successful and False if the username is taken</returns>
	bool Register(); //i used lower case "register", because it's reserved word

	/// The bussines logic for login with existing user
	/// 
	/// It can be unsuccessful if the username is wrong or the password is wrong
	/// <returns>True if the login is successful and False if there is already logged User or unsuccessful authentication </returns>
	bool login();

	/// The bussines logic behind the logout 
	/// 
	/// <returns>True if the logout is successful and False if there is no logged User </returns>
	bool logout();


	//methods that need logged in user 

	/// The logic behind changing username
	///
	/// <returns>True if the change is successful and False if its not or there is no logged User</returns>
	bool change_username();

	/// The logic behind changing password
	///
	/// <returns>True if the change is successful and False if its not or there is no logged User</returns>
	bool change_password();

	/// The logic behind changing birthday
	///
	/// <returns>True if the change is successful and False if its not or there is no logged User </returns>
	bool change_birthday();

	/// The logic behind changing fullname
	///
	/// <returns>True if the change is successful and False if its not or there is no logged User </returns>
	bool change_fullname();

	/// The logic for adding favorite genre
	/// 
	/// <returns>True if it was successful and False if there is no logged User</returns>
	bool add_favorite_genre();

	/// The logic for removing favorite genre
	/// 
	/// <returns>True if it was successful and False if there is no logged User</returns>
	bool remove_favorite_genre();

	/// The logic for creating a song
	/// 
	/// <returns>True if it was successful and False if the song already exists or there is no logged User</returns>
	bool create_song();

	/// The logic behind Rating a Song by User
	/// 
	/// Rating should be in interval [2.00,6.00]
	/// <returns>True if the Rating is saved and False if there is no Song with that name,already User voted for this Song, or there is no logged User </returns>
	bool rate_song();

	/// Big bussines logic for generating playlist
	/// 
	/// Takes user input for the size of the playlsit and the criterias, and passes it to evaluate(const std::string _expression)
	/// then calls fill(std::vector<Song> &_songs, const size_t _final_size)
	/// and assigns it to playlist with creators id and songs
	/// <returns>False only if there is no logged User, otherwise True </returns>
	bool generating_playlist();

	/// Saves a playlist to the database
	/// 
	/// Saves the current playlist with name and creator id
	/// <returns>True if the save is successful, False if there is existing playlist with this name and creator, there is no logged User or playlist is empty</returns>
	bool save_playlist();

	/// Loads playlist by name and logged user
	/// 
	/// To prevent loading other users playlists, you have to be logged, which takes users id
	/// <returns>True if playlist is successfully loaded, False if there is no logged User or there is no playlist with the given name</returns>
	bool load_playlist();

	/// Business logic behind printing the currently loaded playlist
	/// 
	/// <returns>True if the print is successful and False if there is no logged User or no loaded playlist</returns>
	bool print_playlist();

	/// Prints all names of Users Playlists
	void my_playlists();

	/// Prints Users information
	void user_info();

private:
	/// Pointer to successfully logged User
	User* user;

	/// Pointer to the loaded playlist
	Playlist* playlist;

	/// Database context
	Context db;
private:

	/// Vector of all Song with rating above given number
	/// 
	/// <returns>vector of Song</returns>
	std::vector<Song> songs_above_rating();

	/// Vector of all Songs with genres that are in list of desired genres
	/// 
	/// <returns>vector of Song</returns>
	std::vector<Song> songs_with_genres(std::vector<std::string> _genres = std::vector<std::string>());

	/// Vector of all Songs that are with different genres from the list of desired genres
	/// 
	/// <returns>vector of Song</returns>
	std::vector<Song> songs_without_genres();

	/// Vector of all Song with release year (before/after/from) a given year
	/// 
	/// 
	/// <param name="keyword">(before/after/from)</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> songs_by_release_year(const std::string keyword);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_option">one of the supported criterias (in help function or in the start of generating)</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> filter(const std::string _option);

	/// Evaluates the given expression recursively
	/// 
	/// <param name="_expression">expression of combined criterias</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> evaluate(const std::string _expression);

	/// Merging two vectors of Songs with operator OR
	/// 
	/// New vector is combination of left hand side vector and songs from the right hand side vector 
	/// ONLY if they are not in the result yet.
	/// <param name="_l">left hand side vector of Songs</param>
	/// <param name="_r">right hand side vector of Songs</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> merge_or(const std::vector<Song> _l, const std::vector<Song> _r);

	/// Merging two vectors of Songs with operator AND
	/// 
	/// The result is vector of Songs that are in both left and right hand side vector
	/// <param name="_l">left hand side vector of Songs</param>
	/// <param name="_r">right hand side vector of Songs</param>
	/// <returns>vector of Song</returns>
	std::vector<Song> merge_and(const std::vector<Song> _l, const std::vector<Song> _r);

	/// Gets the next token 
	/// 
	/// Gets the next token from stringstream _s and saves it in _str
	/// <param name="_s">stringstream by reference</param>
	/// <param name="_str">string by reference</param>
	/// <returns>True if there is next token, False if there is not</returns>
	bool get_next_token(std::stringstream& _s, std::string& _str);

	/// Fills vector of Song with Songs from the database
	/// 
	/// Calculates how many songs it needs to fill to _final_size
	/// <param name="_songs">current vector of Song by reference</param>
	/// <param name="_final_size">desired final size of the vector of Song</param>
	void fill(std::vector<Song> &_songs, const size_t _final_size);
};
	