#pragma once
#include "Playlist.h"

Playlist::Playlist() {}
Playlist::~Playlist() {}

/// Simple print function 
/// 
/// Calls the print function of every Song in the playlist
void Playlist::print_all_songs()
{
	for (Song s : songs)
	{
		std::cout << std::endl;
		s.print();
	}
}