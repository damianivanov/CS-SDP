#pragma once

class Song
{
public:
	Song();
	~Song();

private:
	std::string artist;
	std::string name;
	std::string genre;
	float rating;
	std::string album;
	time_t release_year;

};
