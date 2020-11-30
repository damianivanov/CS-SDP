#pragma once
#include <iostream>
#include <ctime>
class Song
{
public:
	Song();
	Song(std::string _artist, std::string _name, std::string _genre, float _rating, std::string album, tm _release_year);
	~Song();

private:
	std::string artist;
	std::string name;
	std::string genre;
	float rating;
	std::string album;
	struct tm release_year;

};
