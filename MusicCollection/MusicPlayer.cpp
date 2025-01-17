#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :user(nullptr), playlist(nullptr) {}
MusicPlayer::~MusicPlayer() {
	user = nullptr;
	playlist = nullptr;
}

//Working with user
void MusicPlayer::Register()
{
	std::cout << "--------Register--------" << std::endl;
	std::string username;
	std::cout << "Enter a username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');
	while (!db.available_username(username))
	{
		std::cout << username << " is already taken" << std::endl;
		std::cout << "Enter a username: ";
		username.clear();
		std::cin >> username;
		std::cin.ignore(INT_MAX, '\n');
	}

	std::string password;
	std::cout << "Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512().addData(password.c_str(), password.length()).finalize().toString();

	std::string fullname;
	std::cout << "Enter a fullname: ";
	std::getline(std::cin, fullname);
	clear_whitespaces(fullname);

	std::string birthday;
	std::cout << "Enter your birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');

	User new_user(username, password, fullname, birthday, new_guid());
	db.add_user(new_user);
	std::cout << "Successfully registered " << new_user.get_username() << std::endl;
}
bool MusicPlayer::login()
{
	if (logged())
	{
		std::cout << "You have to loggout first" << std::endl;
		return false;
	}
	std::cout << "--------Login--------" << std::endl;
	std::string username;
	std::cout << "Enter a username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');

	std::string password;
	std::cout << "Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');

	password = Chocobo1::SHA3_512().addData(password.c_str(), password.length()).finalize().toString();

	if (db.login_validation(username, password)) {
		user = db.get_user_by_username(username); // the only line that user can be assigned
		std::cout << "Successfully logged in as " << user->get_username() << std::endl;
		return true;
	}
	std::cout << "Login failed " << std::endl;
	return false;
}
void MusicPlayer::logout()
{
	std::cout << "Successfully logged out from " << user->get_username() << std::endl;
	user = nullptr;
}

//functionality for logged users
bool MusicPlayer::create_song()
{
	std::cout << "--------Creating Song--------" << std::endl;
	std::string name;
	std::cout << "Enter song name: ";
	std::getline(std::cin, name);
	clear_whitespaces(name);

	std::string artist;
	std::cout << "Enter the artist: ";
	std::getline(std::cin, artist);
	clear_whitespaces(artist);

	std::string genre;
	std::cout << "Enter the genre: ";
	std::getline(std::cin, genre);
	clear_whitespaces(genre);

	std::string album;
	std::cout << "Enter the album: ";
	std::getline(std::cin, album);
	clear_whitespaces(album);

	int release_year;
	std::cout << "Enter the release year: ";
	std::cin >> release_year;
	std::cin.ignore(INT_MAX, '\n');

	Song s(new_guid(), artist, name, genre, album, release_year);

	if (db.add_song(s))
	{
		std::cout << "Successfully added: " << s.get_name() << " by: " << s.get_artist() << std::endl;
		return true;
	}
	std::cout << s.get_name() << " by: " << s.get_artist() << " already exists" << std::endl;
	return false;
}
bool MusicPlayer::add_favorite_genre()
{
	std::cout << "--------Add a genre--------" << std::endl;
	std::string genre;
	std::cout << "Enter a new favorite genre: ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');
	user->add_favorite_genre(genre);
	return false;
}
bool MusicPlayer::remove_favorite_genre()
{
	std::cout << "--------Remove a genre--------" << std::endl;
	std::string genre;
	std::cout << "Enter a genre to remove " << genres_print(user->get_favorite_genres()) << ": ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');
	user->remove_favorite_genre(genre);
	return true;
}
bool MusicPlayer::rate_song()
{
	std::cout << "--------Rate a song--------" << std::endl;
	std::string song_name;
	std::cout << "Enter a song name to rate: ";
	std::getline(std::cin, song_name);
	clear_whitespaces(song_name);

	std::string artist;
	std::cout << "Enter the artist of the song: ";
	std::getline(std::cin, artist);
	clear_whitespaces(artist);

	float rating;
	std::cout << "Enter the rating: ";
	std::cin >> rating;
	std::cin.ignore(INT_MAX, '\n');
	if (rating > 6.00 || rating < 2.00)
	{
		std::cout << "Invalid rating, the value should be between 2.00 and 6.00" << std::endl;
		return false;
	}
	Song* song = db.get_song_by_name_and_artist(song_name, artist);

	if (song != nullptr)
	{
		return vote_song(song, rating);
	}
	std::cout << "There is no song called " << song_name << " by " << artist << std::endl;
	return false;
}

//Changing User info
void MusicPlayer::change_fullname()
{
	std::cout << "--------Chaning Fullname--------" << std::endl;
	std::string fullname;
	std::cout << "Enter new fullname: ";
	std::getline(std::cin, fullname);
	clear_whitespaces(fullname);
	user->set_fullname(fullname);
	std::cout << "Successfully changed your fullname. " << std::endl;
}
void MusicPlayer::change_birthday()
{
	std::cout << "--------Chaning Birthday--------" << std::endl;
	std::string birthday;
	std::cout << "Enter your new birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');
	user->set_birthday(birthday);
	std::cout << "Successfully changed your birthday. " << std::endl;
}
bool MusicPlayer::change_password()
{
	std::cout << "--------Chaning Password--------" << std::endl;
	std::string password;
	std::cout << "Enter your OLD password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	if (password == user->get_password())
	{
		std::string new_password, confirm_password;
		std::cout << "Enter your new password: ";
		std::cin >> new_password;
		std::cin.ignore(INT_MAX, '\n');

		std::cout << "Confrim your new password: ";
		std::cin >> confirm_password;
		std::cin.ignore(INT_MAX, '\n');

		if (confirm_password == new_password)
		{
			new_password = Chocobo1::SHA3_512()
				.addData(new_password.c_str(), new_password.length())
				.finalize()
				.toString();

			user->set_password(new_password);
			std::cout << "Successfully changed your password. " << std::endl;
			return true;
		}
		else
		{
			std::cout << "Failed to confirm the new password." << std::endl;
			return false;
		}

	}
	std::cout << "Wrong password." << std::endl;
	return false;;
}
bool MusicPlayer::change_username()
{
	std::cout << "--------Chaning Username--------" << std::endl;
	std::string username;
	std::cout << "Enter a new username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');

	if (db.available_username(username))
	{
		user->set_username(username);
		std::cout << "Successfully changed your username. " << std::endl;
		return true;
	}
	std::cout << username << " is already taken." << std::endl;
	return false;
}

bool MusicPlayer::load_playlist()
{
	std::cout << "--------Loading a playlist--------" << std::endl;
	std::string name;
	std::cout << "Enter playlist name: ";
	std::getline(std::cin, name);
	clear_whitespaces(name);

	playlist = db.get_playlist_by_name_and_user_id(name, user->get_id());

	if (playlist != nullptr)
	{
		std::cout << "Successfully loaded playlist called " << name << " with " << playlist->get_songs().size() << " songs:" << std::endl;
		playlist->print_all_songs();
		return true;
	}
	std::cout << "There is no playlist called " << name << std::endl;
	return false;
}
bool MusicPlayer::save_playlist()
{
	std::cout << "--------Saving Playlist--------" << std::endl;
	if (playlist == nullptr)
	{
		std::cout << "Can't save empty playlist" << std::endl;
		return false;
	}

	std::string name;
	std::cout << "Enter playlist's name: ";
	std::getline(std::cin, name);
	clear_whitespaces(name);
	this->playlist->set_name(name);

	if (db.add_playlist(*playlist))
	{
		std::cout << "Successfully added playlist: " << playlist->get_name() << " with " << playlist->get_songs().size() << " songs!" << std::endl;
		return true;
	}

	std::cout << "Playlist " << playlist->get_name() << " already exists!" << std::endl;
	return true;
}
bool MusicPlayer::generating_playlist()
{
	std::cout << "--------Generating a playlist--------" << std::endl;

	std::cout << "Enter multiple criterias ordered by priority and combined with operators AND , OR and (): " << std::endl;
	std::cout << "	-Songs with rating ABOVE the given rating ---> above" << std::endl;
	std::cout << "	-Songs WITH certain genres ---> with" << std::endl;
	std::cout << "	-Songs WITHOUT certain genres ---> without" << std::endl;
	std::cout << "	-Songs within the FAVORITE genres ---> favorite" << std::endl;
	std::cout << "	-Songs FROM release year ---> from" << std::endl;
	std::cout << "	-Songs AFTER release year ---> after" << std::endl;
	std::cout << "	-Songs BEFORE release year ---> before" << std::endl;
	std::cout << "	-All songs ---> all" << std::endl;

	std::string line;
	std::cout << "> ";
	std::getline(std::cin, line);
	clear_whitespaces(line);

	std::vector<Song> songs;
	if (line == "all")
		songs = db.get_n_ordered_songs(db.get_all_songs().size());
	/*After submission
	* not sorting the songs will be way faster
	* songs = db.get_all_songs();
	*/
	else
	{
		size_t songs_count;
		std::cout << "Enter a song count: ";
		std::cin >> songs_count;
		std::cin.ignore(INT_MAX, '\n');
		songs = evaluate(line);
		int size_before_fill = songs.size(); // not needed after some refactoring
		std::cout << "Songs from the search query: " << size_before_fill << std::endl;
		fill(songs, songs_count);
		std::cout << "Songs after filling up songs: " << songs.size() << std::endl;
	}
	playlist = new Playlist();
	playlist->set_songs(songs);
	playlist->set_creator(user->get_id());
	std::cout << "Successfully generated playlist with " << playlist->get_songs().size() << " songs!" << std::endl;
	return true;
}
void MusicPlayer::my_playlists()
{
	std::vector<std::string> playlists = db.get_all_playlists_by_cretor_id(user->get_id());
	std::cout << "All playlists by: " << user->get_username() << std::endl;
	for (std::string name : playlists)
		std::cout << " - " << name << std::endl;
}
void MusicPlayer::user_info()
{
	user->print_user();
}
bool MusicPlayer::print_playlist()
{
	if (playlist != nullptr)
	{
		playlist->print_all_songs();
		return true;
	}
	std::cout << "There is no loaded playlist!" << std::endl;
	return false;
}
bool MusicPlayer::vote_song(Song* _song, float _rating)
{
	if (db.rated_song(user->get_id(), _song->get_id()))
	{
		std::cout << "Already voted for " << _song->get_name() << " by " << _song->get_artist() << std::endl;
		return false;
	}

	std::vector<Rating> ratings = db.get_ratings_by_song_id(_song->get_id());
	float new_rating = 0.0;
	/*
		After the submission
		float new_rating= _song->get_rating()*ratings.size();
		instead of the for loop
		after the change this will be O(const) complexity, instead of O(n) (linear)
	*/

	for (Rating r : ratings)
	{
		new_rating += r.rating;
	}
	new_rating += _rating;
	new_rating /= ratings.size() + 1;

	_song->set_rating(new_rating);
	db.add_rating(user->get_id(), _song->get_id(), _rating);
	std::cout << "You rated with " << _rating << " " << _song->get_name() << " by " << _song->get_artist() << std::endl;
	return true;
}

std::vector<Song> MusicPlayer::songs_above_rating()
{
	float rating;
	std::cout << "Minimum rating: ";
	std::cin >> rating;
	std::cin.ignore(INT_MAX, '\n');
	std::vector<Song> songs = db.get_songs_by_rating(rating);
	return songs;
}
std::vector<Song> MusicPlayer::songs_with_genres(std::vector<std::string> _genres)
{
	std::vector<Song> songs;
	if (_genres.empty())
	{
		std::string line, tmp;
		std::cout << "One or more genres (seperated only with commas): ";
		std::getline(std::cin, line);
		clear_whitespaces(line);

		std::stringstream s(line);
		while (std::getline(s, tmp, ','))
			_genres.push_back(tmp);
	}

	songs = db.get_songs_by_list_of_genres(_genres);
	return songs;
}
std::vector<Song> MusicPlayer::songs_without_genres()
{
	//if there are no favorite genres
	std::vector<std::string> genres;
	std::string line, tmp;
	std::cout << "One or more genres (seperated only with commas): ";
	std::getline(std::cin, line);
	clear_whitespaces(line);

	std::stringstream s(line);
	while (std::getline(s, tmp, ','))
		genres.push_back(tmp);
	std::vector<Song> songs = db.get_songs_except_genres(genres);
	return songs;
}
std::vector<Song> MusicPlayer::songs_by_release_year(const std::string keyword)
{
	int year = 0;
	// before,from,after
	std::cout << keyword << " year: ";
	std::cin >> year;
	std::cin.ignore(INT_MAX, '\n');

	std::vector<Song> songs;
	if (keyword == "from")
		songs = db.get_songs_from_year(year);
	else if (keyword == "before")
		songs = db.get_songs_before_year(year);
	else if (keyword == "after")
		songs = db.get_songs_after_year(year);

	return songs;
}

std::vector<Song> MusicPlayer::filter(std::string _option)	
{
	transform(_option.begin(), _option.end(), _option.begin(), ::tolower);

	if (_option == "above")
		return songs_above_rating();
	else if (_option == "with")
		return songs_with_genres();
	else if (_option == "without")
		return songs_without_genres();
	else if (_option == "favorite")
		return songs_with_genres(user->get_favorite_genres());
	else if (_option == "from" || _option == "after" || _option == "before")
		return songs_by_release_year(_option);
	else
	{
		std::cout << _option << " is not valid criteria " << std::endl;
		return std::vector<Song>();
	}
}
std::vector<Song> MusicPlayer::evaluate(const std::string _expression)
{
	// after AND (before AND favorite) AND above
	std::string left_token, right_token;
	std::stringstream s(_expression);
	std::vector<Song> songs;
	while (get_next_token(s, right_token))
	{
		if (right_token == "AND")
		{
			get_next_token(s, right_token);
			if (is_expression(right_token) || is_expression(left_token)) // => expression
			{
				if (songs.empty())
				{
					songs = merge_and(evaluate(left_token), evaluate(right_token));
					left_token.clear();
					right_token.clear();
				}
				else
				{
					songs = merge_and(songs, evaluate(right_token));
					right_token.clear();
				}
			}
			else
			{
				if (left_token.empty())
					songs = merge_and(songs, filter(right_token));
				else
				{
					//filter should be used only if we are sure there are no expressions
					// here this is assured by the first if and there is value in both
					songs = merge_and(filter(left_token), filter(right_token));
					left_token.clear();
					right_token.clear();
					// so we dont go to the last if which is for cases when there is a single criteria
				}
			}
		}
		else if (right_token == "OR")
		{
			get_next_token(s, right_token);
			if (is_expression(right_token) || is_expression(left_token)) // => expression 
			{
				if (songs.empty())
				{
					songs = merge_or(evaluate(left_token), evaluate(right_token));
					left_token.clear();
					right_token.clear();
				}
				else
				{
					songs = merge_or(songs, evaluate(right_token));
					right_token.clear();
				}
			}
			else
			{
				if (left_token.empty())
					songs = merge_or(songs, filter(right_token));
				else
				{
					songs = merge_or(filter(left_token), filter(right_token));
					// so we dont go to the last if which is for cases when there is a single criteria
					left_token.clear();
					right_token.clear();
				}
			}
		}
		else
			left_token = right_token;
	}
	//single criteria: "after","favorite" etc. //edit it can be expression ()
	// this is one of the base cases for the recursion of evaluate
	if (songs.empty() && !left_token.empty())
	{
		if (is_expression(left_token))
			songs = evaluate(left_token);
		else
			songs = filter(left_token);
	}
	return songs;
}
void MusicPlayer::fill(std::vector<Song>& _songs, const size_t _final_size)
{
	// if _song is with more songs then the _final_size, we take the first _final_size songs
	std::vector<Song>::iterator end = std::next(_songs.begin(), std::min(_final_size, _songs.size()));
	std::vector<Song> songs(_songs.begin(), end);

	if (songs.size() < _final_size)
	{
		size_t songs_to_fill = _final_size - songs.size();
		std::vector<Song> fillers = db.get_n_ordered_songs(songs_to_fill + _songs.size()); // the worst case scenario the songs after the query are sorted
		_songs = merge_or(_songs, fillers);
		if (_songs.size() > _final_size)
		{
			_songs.erase(_songs.end() - (_songs.size() - _final_size), _songs.end());
		}
	}
	else
		_songs = songs;

}