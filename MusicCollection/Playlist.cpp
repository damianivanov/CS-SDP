#pragma once
#include "Playlist.h"

Playlist::Playlist():creator(nullptr){}

Playlist::~Playlist()
{}

void Playlist::print_all_songs()
{
	std::cout << name << " with " << songs.size() << " songs:" << std::endl;
	for (auto x : this->songs)
	{
		std::cout << '\t';
		x.print();
	}
}

void Playlist::add_song(const Song song)
{
	if (!std::count(songs.begin(), songs.end(), song))
	{
		songs.push_back(song);
		std::cout << song.get_name() << " added in the Playlist" << std::endl;
	}
	else
		std::cout << song.get_name() << " already in the Playlist" << std::endl;
}
