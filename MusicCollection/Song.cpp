#pragma once
#include "Song.h"

Song::Song() :artist(""), name(""), genre(""),
			rating(0.0f), album("")
{
	time_t now = time(0);
	localtime_s(&release_year, &now);
}

Song::Song(std::string _artist, std::string _name, std::string _genre, float _rating, std::string _album, tm _release_year)
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
