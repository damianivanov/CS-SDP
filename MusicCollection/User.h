#pragma once
#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
#include "Guid.cpp"
#include "StringHelpers.cpp"
#include "Playlist.h"
class Playlist;

/// Representation of a User and his information
///
class User
{
public:
	/// Default constructor
	/// 
	/// assigns all strings to empty strings, and the birthday for 1900
	User();

	/// Constructor with parameters
	/// 
	/// assigns all of the properties with the given values
	/// <param name="_username">username</param>
	/// <param name="_password">password</param>
	/// <param name="_fullname">fullname</param>
	/// <param name="_birthday">birthday</param>
	/// <param name="_id">id</param>
	/// <param name="_favorite_genres">vector with favorite genres</param>
	User(std::string _username, 
		std::string _password, 
		std::string _fullname, 
		std::string _birthday, 
		std::string _id="",
		std::vector<std::string> _favorite_genres = std::vector<std::string>()
		);
	~User();

	//getters

	/// Simple getter for the username
	///
	/// @returns username
	const std::string get_username() const { return this->username; }

	/// Simple getter for the password
	///
	/// @returns the hashed password
	const std::string get_password() const { return this->password; }

	/// Simple getter for the fullname
	///
	/// @returns the fullname
	const std::string get_fullname() const { return this->fullname; }

	/// Simple getter for the identification
	///
	/// @returns the identification
	const std::string get_id() const { return this->id; }

	/// Simple getter for the birthday
	///
	/// @returns the birthday in tm structure
	const tm get_birthday() const { return this->birthday; }

	/// Simple getter for the vector of favorite genres
	///
	/// @returns the vector with the favorite genres
	const std::vector<std::string> get_favorite_genres() const { return this->favorite_genres; }

	//setters
	/// Simple setter for the username
	///
	/// @param _username - desired new username
	void set_username(std::string _username) { this->username = _username; }

	/// Simple setter for the password
	///
	/// @param _password - desired new password
	void set_password(std::string _password) { this->password = _password; }

	/// Simple setter for the fullname
	/// 
	/// @param _fullname  - new fullname
	void set_fullname(std::string _fullname) { this->fullname = _fullname; }

	/// Simple setter for the id
	/// 
	/// @param _id - new id 
	void set_id(std::string _id) { this->id = _id; }

	/// @param the vector with the favorite genres
	/// 
	/// @param _favorite_genres - vector with the new favorite genres
	void set_favorite_genres(std::vector<std::string> _favorite_genres) { this->favorite_genres = _favorite_genres; }

	/// Simple setter for the birthday
	/// 
	/// @param _birthday - new birthday string
	void set_birthday(std::string _birthday) { this->birthday = string_to_tm(_birthday); }

	/// Adds genre from favorites, if it's not in the list already
	/// 
	/// @param _genre - adds the given genre from the list with favorites
	void add_favorite_genre(std::string _genre);

	/// Removes genre from favorites, if the genre is in the list
	/// 
	/// @param _genre - removes the given genre from the list with favorites
	void remove_favorite_genre(std::string _genre);

	/// Beautiful print for User 
	/// 
	/// used only for printing in console, not in any business logic
	/// @returns beautiful string containing all information about User
	void print_user();

private:

	/// Unique username for every User
	///
	/// 
	std::string username;

	/// Hashed version of User's password
	/// 
	/// Every password is hashed withg SHA3_512() method
	std::string password;

	/// User's fullname
	///
	///
	std::string fullname;

	/// Representation of birth date for the User
	///	
	/// accepts only DD/MM/YYYY format
	tm birthday;

	/// list of User's favorite genres
	/// 
	/// 
	std::vector<std::string> favorite_genres;

	/// Unique identification for every User 
	/// 
	/// GUID generated when objected is created with new_guid() - extremely low chances of duplicates
	std::string id;

};