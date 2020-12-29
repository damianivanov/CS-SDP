#pragma once
#include "Playlist.h"

Playlist::Playlist() {}
Playlist::~Playlist(){}

void Playlist::print_all_songs()
{
	for (Song s : songs)
	{
		std::cout << std::endl;
		s.print();
	}
}
void Playlist::add_song(Song song)
{
	if (songs.size()==0 || !std::count(songs.begin(), songs.end(), song))
	{
		songs.push_back(song);
		std::cout << song.get_name() << " added in the Playlist" << std::endl;
	}
	else
		std::cout << song.get_name() << " already in the Playlist" << std::endl;
}
