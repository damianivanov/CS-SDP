#pragma once
#include "Playlist.h"

Playlist::Playlist():creator(nullptr) {}

Playlist::~Playlist()
{
	delete creator;
}

void Playlist::add_song(const Song* song)
{
	if (!std::count(songs.begin(), songs.end(), song))
	{
		songs.push_back(song);
		std::cout << song->get_name() << " added in the Playlist" << std::endl;
	}
	else
		std::cout << song->get_name() << " already in the Playlist" << std::endl;
}
