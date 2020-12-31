#pragma once
#include <iostream>

//structure for many to many table in database
struct Rating
{
	std::string user_id;
	std::string song_id;
	float rating=0.0;
};