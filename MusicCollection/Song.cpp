#pragma once
#include "Song.h"

Song::Song() :artist(""), name(""), genre(""),
			rating(0.0f), album(""),release_year(1900){}

Song::Song(std::string _artist, std::string _name, std::string _genre, float _rating, std::string _album, int _release_year)
{
	artist =_artist ;
	name = _name ;
	genre= _genre;
	rating = _rating;
	album = _album;
	release_year = _release_year;
}

Song::~Song()
{
}

bool Song::operator==(const Song& other)
{
	return *this == other;
}

void Song::print()
{
	std::cout << "Song name: " << name << std::endl;
	std::cout << "Artist: " << artist << std::endl;
	std::cout << "Genre: " << genre << std::endl;
	std::cout << "Rating: " << rating << std::endl;	
	std::cout << "Album: " << album << std::endl;	
	std::cout << "Release Year: " << release_year << std::endl;	
}

