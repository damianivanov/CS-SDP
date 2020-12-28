#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :user(nullptr),playlist(nullptr) {}
MusicPlayer::~MusicPlayer() {}

//functionality for logged users
bool MusicPlayer::create_song()
{
	if (!logged())
	{
		std::cout << "To be able to create a song you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Creating Song--------" << std::endl;
	std::string name;
	std::cout << "Enter song name: ";
	std::getline(std::cin, name);

	std::string artist;
	std::cout << "Enter the artist: ";
	std::getline(std::cin, artist);

	std::string genre;
	std::cout << "Enter the genre: ";
	std::getline(std::cin, genre);

	std::string album;
	std::cout << "Enter the album: ";
	std::getline(std::cin, album);

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
	if (!logged())
	{
		std::cout << "To be able to add a genre, you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Add a genre--------" << std::endl;
	std::string genre;
	std::cout << "Enter favorite genre: ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');
	user->add_favorite_genre(genre);
	return false;
}
bool MusicPlayer::remove_favorite_genre()
{
	if (!logged())
	{
		std::cout << "To be able to remove a genre, you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Remove a genre--------" << std::endl;
	std::string genre;
	std::cout << "Enter a genre to remove a genre from " << user->genres_print()<<": ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');
	user->remove_favorite_genre(genre);
	return true;
}
bool MusicPlayer::rate_song()
{
	if (!logged())
	{
		std::cout << "To be able to rate a song, you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Rate a song--------" << std::endl;
	std::string song_name;
	std::cout << "Enter a song name to rate: ";
	std::getline(std::cin, song_name);

	std::string artist;
	std::cout << "Enter the artist of the song: ";
	std::getline(std::cin, artist);

	float rating;
	std::cout << "Enter the rating: ";
	std::cin >> rating;
	std::cin.ignore(INT_MAX, '\n');

	Song* song = db.get_song_by_name_and_artist(song_name, artist);

	if (song!=nullptr)
	{
		float new_rating = 0.0;
		if (db.rated_song(user->get_id(), song->get_id()))
		{
			std::cout << "Already voted for " << song_name << " by " << artist << std::endl;
			return false;
		}
		std::vector<Rating> ratings=db.get_ratings_by_song_id(song->get_id());
		for (auto r:ratings)
		{
			new_rating += r.rating;
		}
		new_rating += rating;
		new_rating /= ratings.size() + 1;

		song->set_rating(new_rating);
		db.add_rating(user->get_id(), song->get_id(), rating);
		std::cout << "You rated with "<<rating<<" "<< song->get_name() << " by " << song->get_artist() << std::endl;
		return true;
	}
	std::cout << "There is no song called " << song_name << " by " << artist << std::endl;
	return false;
}

//Changing User info
bool MusicPlayer::change_fullname()
{
	if (!logged())
	{
		std::cout << "To be change your full name, you have to be logged in. " << std::endl;
		return false;
	}
	std::string fullname;
	std::cout << "Enter new fullname: ";
	std::getline(std::cin, fullname);
	user->set_fullname(fullname);
	std::cout << "Successfully changed your fullname. " << std::endl;
	return true;
}
bool MusicPlayer::change_password()
{
	if (!logged())
	{
		std::cout << "To be able to change your password, you have to be logged in. " << std::endl;
		return false;
	}
	std::string password;
	std::cout << "Enter your OLD password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	if (password==user->get_password())
	{
		std::string new_password;
		std::cout << "Enter your new password: ";
		std::cin >> new_password;
		std::cin.ignore(INT_MAX, '\n');
		new_password = Chocobo1::SHA3_512()
			.addData(new_password.c_str(), new_password.length())
			.finalize()
			.toString();
		user->set_password(new_password);
		std::cout << "Successfully changed your password. " << std::endl;
		return true;
	}
	std::cout << "Wrong password." << std::endl;
	return false;;
}
bool MusicPlayer::change_birthday()
{
	if (!logged())
	{
		std::cout << "To be able to change your birthday, you have to be logged in. " << std::endl;
		return false;
	}
	
	std::string birthday;
	std::cout << "Enter your new birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');
	user->set_birthday(birthday);
	std::cout << "Successfully changed your birthday. " << std::endl;
	return true;
}
bool MusicPlayer::change_username()
{
	if (!logged())
	{
		std::cout << "To be able to change your username, you have to be logged in. " << std::endl;
		return false;
	}
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

//Generating playlist
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
	std::stringstream s(line);
	while (std::getline(s, tmp, ','))
		genres.push_back(tmp);
	std::vector<Song> songs = db.get_songs_except_genres(genres);
	return songs;
}
std::vector<Song> MusicPlayer::songs_by_release_year(const std::string keyword)
{
	int year=0;
	std::cout << "Choose a year: ";
	std::cin >> year;
	std::cin.ignore(INT_MAX, '\n');

	std::vector<Song> songs;
	if (keyword == "from")
		songs = db.get_songs_from_year(year);
	else if(keyword == "before")
		songs = db.get_songs_before_year(year);
	else if (keyword == "after")
		songs = db.get_songs_after_year(year);

	return songs;
}

bool MusicPlayer::generating_playlist()
{
	if (!logged())
	{
		std::cout << "To be able to generate playlist, you have to be logged in. " << std::endl;
		return false;
	}
	size_t songs_count;
	std::cout << "--------Generating a playlist--------" << std::endl;
	std::cout << "Enter a song count: ";
	std::cin >> songs_count;
	std::cin.ignore(INT_MAX, '\n');

	std::cout << "Enter multiple criterias ordered by priority and combined with operators AND , OR: " << std::endl;
	std::cout << "	-Songs with rating ABOVE the given rating ---> above" << std::endl;
	std::cout << "	-Songs WITH certain genres ---> with" << std::endl;
	std::cout << "	-Songs WITHOUT certain genres ---> without" << std::endl;
	std::cout << "	-Songs within the FAVORITE genres ---> favorite" << std::endl;
	std::cout << "	-Songs FROM release year ---> from" << std::endl;
	std::cout << "	-Songs AFTER release year ---> after" << std::endl;
	std::cout << "	-Songs BEFORE release year ---> before" << std::endl;
																										
	std::string line;
	std::getline(std::cin, line);

	std::vector<Song> songs = evaluate(line);
	fill(songs, songs_count);
	this->playlist->set_songs(songs);
	this->playlist->set_creator(user->get_id());

	return true;
}
bool MusicPlayer::load_playlist()
{
	if (!logged())
	{
		std::cout << "To be able to load a playlist, you have to be logged in. " << std::endl;
		return false;
	}
	
	std::cout << "--------Loading a playlist--------" << std::endl;
	std::string name;
	std::cout << "Enter playlist name: ";
	std::cin >> name;
	std::cin.ignore(INT_MAX, '\n');
	playlist = db.get_playlist_by_name_and_user_id(name,user->get_id());
	//TODO playlist should be nullptr
	if (playlist->get_creator_id()!= "")
	{
		playlist->print_all_songs();
		return true;
	}
	std::cout << "There is no playlist called " << name << std::endl;
	return false;
}
bool MusicPlayer::save_playlist()
{
	if (!logged())
	{
		std::cout << "To save the playlist, you have to be logged in. " << std::endl;
		return false;
	}
	std::string name;
	std::cout << "Enter playlist's name: ";
	std::getline(std::cin, name);
	this->playlist->set_name(name);
	if (db.add_playlist(*playlist))
	{
		std::cout << "Successfully added playlist: " << playlist->get_name() << " with " << playlist->get_songs().size() <<" songs!"<< std::endl;
		return true;
	}
	std::cout << "Playlist " << playlist->get_name() << " already exists!" << std::endl;
	return true;
}
bool MusicPlayer::print_playlist()
{
	if (playlist)
	{
		playlist->print_all_songs();
		return true;
	}
	std::cout << "There is no loaded playlist!"<< std::endl;
	return false;
}

std::vector<Song> MusicPlayer::filter(std::string _option) 
{
	transform(_option.begin(), _option.end(), _option.begin(), ::tolower);

	if (_option == "above")
		return songs_above_rating();
	else if (_option == "with")
		return songs_with_genres();	
	else if(_option == "without")
		return songs_without_genres();
	else if(_option == "favorite")
		return songs_with_genres(user->get_favorite_genres());
	else if(_option == "from" || _option == "after" || _option == "before")
		return songs_by_release_year(_option);
	else
	{
		std::cout << _option << " is not valid criteria " << std::endl;
		return std::vector<Song>();
	}
}
std::vector<Song> MusicPlayer::evaluate(const std::string _expression)
{
	std::string token,tmp;
	std::stringstream s(_expression);
	std::vector<Song> songs;
	while (get_next_token(s,tmp))
	{
		// above AND (favorite OR after) AND before
		if (tmp == "AND")
		{
			get_next_token(s,tmp);
			if (std::count(tmp.begin(), tmp.end(), ' ') != 0) // => expression
			{
				if (songs.empty())
				{
					songs = merge_and(filter(token), evaluate(tmp));
				}
				else
					songs = merge_and(songs, evaluate(tmp));
			}
			else
				songs = merge_and(filter(token), filter(tmp));
		}
		else if (tmp == "OR")
		{
			get_next_token(s, tmp);
			if (std::count(tmp.begin(), tmp.end(), ' ') != 0) // => expression
			{
				if (songs.empty())
				{
					songs = merge_or(filter(token), evaluate(tmp));
				}
				else
					songs = merge_or(songs, evaluate(tmp));
			}
			else
				songs = merge_or(filter(token), filter(tmp));
		}
		else
			token=tmp;
	}
	return songs;
}

std::vector<Song> MusicPlayer::merge_or(const std::vector<Song> _l, const std::vector<Song> _r)
{
	std::vector<Song> s(_l);
	std::copy_if(_r.begin(), _r.end(), std::back_inserter(s), [&](const Song _song)
		{
			return std::find_if(_l.begin(), _l.end(), [&](const Song s) 
				{
					return s.get_id() == _song.get_id(); 
				}) == _l.end();
		});
	return s;
}
std::vector<Song> MusicPlayer::merge_and(const std::vector<Song> _l, const std::vector<Song> _r)
{
	std::vector<Song> s;
	std::copy_if(_l.begin(), _l.end(), std::back_inserter(s), [&](const Song _song)
		{
			return std::find_if(_r.begin(), _r.end(), [&](const Song s) { return s.get_id() == _song.get_id(); }) != _r.end();
		});
	return s;
}

bool MusicPlayer::get_next_token(std::stringstream& _s,std::string& _str)
{
	_str = "";
	std::getline(_s, _str, ' ');
	if (_str[0] == '(')
	{
		std::string curr_expression = _str.substr(1, _str.size() - 1);
		while (std::getline(_s, _str,' '))
		{
			if (_str[_str.size() - 1] == ')')
				curr_expression += ' ' + _str.substr(0, _str.size() - 1);
			else
				curr_expression +=  ' ' + _str;
		}
		_str = curr_expression;
		return true;

	}
	return _str!="";
}
void MusicPlayer::fill(std::vector<Song> &_songs, size_t _final_size)
{
	auto end = std::next(_songs.begin(), std::min(_final_size, _songs.size()));
	std::vector<Song> songs(_songs.begin(), end);

	if (songs.size() < _final_size)
	{
		size_t songs_to_fill = _final_size - songs.size();
		std::vector<Song> fillers = db.get_n_ordered_songs(songs_to_fill+_songs.size()); // the worst case scenario the songs after the query are sorted
		_songs = merge_or(_songs, fillers);
	}

}

//Working with user
bool MusicPlayer::Register()
{
	std::cout << "--------Register--------" << std::endl;
	std::string username;
	do
	{
		std::cout << "Enter a username: ";
		std::cin >> username;
		std::cin.ignore(INT_MAX, '\n');

	} while (!db.available_username(username));

	std::string password;
	std::cout << "Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	std::string fullname;
	std::cout << "Enter a fullname: ";
	std::getline(std::cin, fullname);

	std::string birthday;
	std::cout << "Enter your birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');
	User new_user(username, password, fullname, birthday, new_guid());
	bool success = db.add_user(new_user);
	if (success)
	{
		std::cout << "Successfully registered " << new_user.get_username() << std::endl;
		return true;
	}
	else {
		std::cout << "User " << user->get_username() << " already exists!" << std::endl;
		return false;
	}

}
bool MusicPlayer::login()
{

	std::cout << "--------Login--------" << std::endl;
	std::string username;
	std::cout << "Enter a username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');

	std::string password;
	std::cout << "Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');

	if (db.login_validation(username, password)) {
		user = db.get_user_by_username(username);
		std::cout << "Successfully logged in as " << user->get_username() << std::endl;
		return true;
	}
	std::cout << "Login failed " << std::endl;
	return false;
}
bool MusicPlayer::logout()
{
	if (logged())
	{
		std::cout << "Successfully logged out from " << user->get_username() << std::endl;
		user = nullptr;
		return true;
	}
	std::cout << "There is no logged user!"<< std::endl;
	return false;
}
