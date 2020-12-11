#pragma once
#include <iostream>
//many to many table
struct Rating
{
	std::string user_id;
	std::string song_id;
	float rating;
};