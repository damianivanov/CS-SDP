#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :user(nullptr) {}

MusicPlayer::MusicPlayer(std::vector<Playlist> _playlists, User* _user) : user(_user), playlists(_playlists) {}
MusicPlayer::~MusicPlayer() {}

bool MusicPlayer::creating_song()
{
	if (!logged())
	{
		std::cout << "To be able to create a song you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Creating Song--------" << std::endl;
	std::string name;
	std::cout << "> Enter song name: ";
	std::cin >> name;
	std::cin.ignore(INT_MAX, '\n');

	std::string artist;
	std::cout << "> Enter the artist: ";
	std::cin >> artist;
	std::cin.ignore(INT_MAX, '\n');

	std::string genre;
	std::cout << "> Enter the genre: ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');

	std::string album;
	std::cout << "> Enter the album: ";
	std::cin >> album;
	std::cin.ignore(INT_MAX, '\n');

	int release_year;
	std::cout << "> Enter the release year: ";
	std::cin >> release_year;
	std::cin.ignore(INT_MAX, '\n');

	Song s(new_guid(), artist, name, genre, album, release_year);
	if (!db.song_exists(s))
	{
		db.add_song(s);
		std::cout << "> Successfully added: " << s.get_name() << " by: " << s.get_artist() << std::endl;
		return true;
	}
	std::cout << "> " << s.get_name() << " by: " << s.get_artist() << " already exists" << std::endl;
	return false;
}
bool MusicPlayer::add_genre()
{
	if (!logged())
	{
		std::cout << "To be able to add a genre, you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Add a genre--------" << std::endl;
	std::string genre;
	std::cout << "> Enter favorite genre: ";
	std::cin >> genre;
	std::cin.ignore(INT_MAX, '\n');
	user->add_favorite_genre(genre);
	return false;
}
bool MusicPlayer::remove_genre()
{
	if (!logged())
	{
		std::cout << "To be able to remove a genre, you have to be logged in. " << std::endl;
		return false;
	}
	std::cout << "--------Remove a genre--------" << std::endl;
	std::string genre;
	std::cout << "> Enter a genre to remove a genre from " << user->genres_print()<<": ";
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
	std::cout << "> Enter a song name to rate: ";
	std::cin >> song_name;
	std::cin.ignore(INT_MAX, '\n');

	std::string artist;
	std::cout << "> Enter the artist of the song: ";
	std::cin >> artist;
	std::cin.ignore(INT_MAX, '\n');

	float rating;
	std::cout << "> Enter the rating: ";
	std::cin >> rating;
	std::cin.ignore(INT_MAX, '\n');

	Song* song = db.get_song_by_name_and_artist(song_name, artist);

	if (song->get_id() != "")
	{
		float new_rating = 0.0;
		if (db.rated_song(user->get_id(), song->get_id()))
		{
			std::cout << "> Already voted for " << song_name << " by " << artist << std::endl;
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
		std::cout << "> You rated with "<<rating<<" "<< song->get_name() << " by " << song->get_artist() << std::endl;
		return true;
	}
	std::cout << "> There is no song called " << song_name << " by " << artist << std::endl;
	return false;
}

bool MusicPlayer::Register()
{
	std::cout << "--------Register--------" << std::endl;
	std::string username;
	do
	{
		std::cout << "> Enter a username: ";
		std::cin >> username;
		std::cin.ignore(INT_MAX, '\n');

	} while (!db.available_username(username));

	std::string password;
	std::cout << "> Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');
	password = Chocobo1::SHA3_512()
		.addData(password.c_str(), password.length())
		.finalize()
		.toString();

	std::string fullname;
	std::cout << "> Enter a fullname: ";
	std::getline(std::cin, fullname);

	std::string birthday;
	std::cout << "> Enter your birtday (ONLY IN DD/MM/YYYY FORMAT): ";
	//maybe valdiation method
	std::cin >> birthday;
	std::cin.ignore(INT_MAX, '\n');
	User new_user(username, password, fullname, birthday, new_guid());
	bool success = db.add_user(new_user);
	if (success)
	{
		std::cout << "> Successfully registered " << new_user.get_username() << std::endl;
		return true;
	}
	else {
		std::cout << "> User " << user->get_username() << " already exists!" << std::endl;
		return false;
	}

}
bool MusicPlayer::login()
{

	std::cout << "--------Login--------" << std::endl;
	std::string username;
	std::cout << "> Enter a username: ";
	std::cin >> username;
	std::cin.ignore(INT_MAX, '\n');

	std::string password;
	std::cout << "> Enter a password: ";
	std::cin >> password;
	std::cin.ignore(INT_MAX, '\n');

	if (db.login_validation(username, password)) {
		user = db.get_user_by_username(username);
		std::cout << "> Successfully logged in as " << user->get_username() << std::endl;
		return true;
	}
	std::cout << "> Login failed " << std::endl;
	return false;
}
