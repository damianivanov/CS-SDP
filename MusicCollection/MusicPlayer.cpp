#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(): user(nullptr) {}
MusicPlayer::MusicPlayer(std::vector<Playlist> _playlists,User* _user): user(_user),playlists(_playlists){}
MusicPlayer::~MusicPlayer()
{
	delete user;
}
