#pragma once
#include <iostream>
#include <ctime>
class Song
{
public:
	Song();
	Song(std::string _artist, std::string _name, std::string _genre, float _rating, std::string album, int _release_year);
	~Song();
	bool operator==(const Song& other);
	const std::string get_artist() const { return this->artist; }
	const std::string get_name() const { return this->name; }
	const std::string get_genre() const { return this->genre; }
	const float get_rating() const { return this->rating; }
	const std::string get_album() const { return this->album; }
	const int get_release_year() const { return this->release_year; }

	void set_artist(std::string _artist) { this->artist = _artist; }
	void set_name(std::string _name) { this->name = _name; }
	void set_genre(std::string _genre) { this->genre = _genre; }
	void set_rating(float _rating) { this->rating =	_rating; }
	void set_album(std::string _album) { this->album = _album; }
	void set_release_year(int _release_year) { this->release_year = _release_year; } //maybe out of scope 

private:
	std::string artist;
	std::string name;
	std::string genre;
	float rating;
	std::string album;
	int release_year;

};
