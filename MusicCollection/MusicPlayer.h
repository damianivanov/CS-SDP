#pragma once
#include <sstream>
#include <limits>
#include "tokenizer.h"
#include "DatabaseContext.h"

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();
	bool logged() { return user!=nullptr; }

	bool Register(); //i used lower case "register", because it's reserved word
	bool login();
	bool logout();
	//methods that need logged in user 
	bool change_username();
	bool change_password();
	bool change_birthday();
	bool change_fullname();

	bool add_favorite_genre();
	bool remove_favorite_genre();
	bool create_song();
	bool rate_song();

	bool generating_playlist();
	bool save_playlist();
	bool load_playlist();
	bool print_playlist();

	void my_playlists();

	


private:
	User* user; //successfully logged  user
	Playlist* playlist;
	Context db;

	std::vector<Song> songs_above_rating();
	std::vector<Song> songs_with_genres(std::vector<std::string> _genres = std::vector<std::string>());
	std::vector<Song> songs_without_genres();
	std::vector<Song> songs_by_release_year(const std::string keyword);

	std::vector<Song> filter(std::string _option);
	std::vector<Song> evaluate(const std::string _expression);

	std::vector<Song> merge_or(const std::vector<Song> _l, const std::vector<Song> _r);
	std::vector<Song> merge_and(const std::vector<Song> _l, const std::vector<Song> _r);

	bool get_next_token(std::stringstream& _s, std::string& _str);
	void fill(std::vector<Song> &_songs, size_t _final_size);
};
	