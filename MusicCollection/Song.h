	#pragma once
#include <iostream>
#include <ctime>
class Song
{
public:
	Song();
	~Song();

	/// Construction Song by: -id,artist,name,genre,album,release year,rating
	Song(std::string _id,std::string _artist, std::string _name, std::string _genre, std::string album, int _release_year, float _rating = 0.0);
	/// <returns>If two songs have the same id, which means they are the same</returns>
	bool operator==(const Song& other) { return this->id == other.id; }

	/// <returns>Artist of the song</returns>
	const std::string get_artist() const { return this->artist; }
	/// <returns>Name of the song</returns>
	const std::string get_name() const { return this->name; }
	/// <returns>Genre of the song</returns>
	const std::string get_genre() const { return this->genre; }
	/// <returns>Rating of the song </returns>
	const float get_rating() const { return this->rating; }
	/// <returns>Album of the song</returns>
	const std::string get_album() const { return this->album; }
	/// <returns>The release year of the song</returns>
	const int get_release_year() const { return this->release_year; }
	/// <returns>Id of the song</returns>
	const std::string get_id() const { return this->id; }

	/// Setter for id
	void set_id(const std::string _id) { this->id = _id; }
	/// Setter for artist
	void set_artist(const std::string _artist) { this->artist = _artist; }
	/// Setter for name
	void set_name(const std::string _name) { this->name = _name; }
	/// Setter for genre
	void set_genre(const std::string _genre) { this->genre = _genre; }
	/// Setter for rating
	void set_rating(const float _rating) { this->rating =	_rating; }
	/// Setter for album
	void set_album(const std::string _album) { this->album = _album; }
	/// Setter for the release year
	void set_release_year(const int _release_year) { this->release_year = _release_year; } //maybe out of scope 

	/// Print function for all of the properties
	void print();

private:

	/// Unique id for every song - GUID
	std::string id;

	/// Name of the artist
	std::string artist;

	/// Name of the song
	std::string name;

	/// Genre of the song
	std::string genre;

	/// Rating of the song - average of all the rates
	float rating;

	/// Name of the album
	std::string album;

	/// Release year of the song 
	int release_year;

};
