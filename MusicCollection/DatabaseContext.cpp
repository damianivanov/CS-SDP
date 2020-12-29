#include "DatabaseContext.h"

//getters like methods
User* Context::get_user_by_username(std::string _username)
{
	for (User& user : users)
	{
		if (user.get_username()==_username)
			return &user;
	}
	return nullptr; 
}
Song* Context::get_song_by_name_and_artist(std::string _name, std::string _artist)
{
	transform(_name.begin(), _name.end(), _name.begin(), ::tolower);
	transform(_artist.begin(), _artist.end(), _artist.begin(), ::tolower);
	for (Song& song : songs)
	{
		std::string name = song.get_name();
		std::string artist = song.get_artist();

		transform(name.begin(), name.end(), name.begin(), ::tolower);
		transform(artist.begin(), artist.end(), artist.begin(), ::tolower);

		if (name == _name && artist==_artist)
			return &song;
	}
	return nullptr;
}
Playlist* Context::get_playlist_by_name_and_user_id(std::string _name, std::string _user_id)
{
	transform(_name.begin(), _name.end(), _name.begin(), ::tolower);
	for (Playlist& playlist: playlists)
	{
		std::string name = playlist.get_name();
		transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name == _name && playlist.get_creator_id() == _user_id)
			return &playlist;
	}
	return nullptr; 
}

std::vector<Rating> Context::get_ratings_by_song_id(std::string _song_id)
{
	std::vector<Rating> all_ratings;
	for (Rating& r:ratings)
	{
		if (r.song_id == _song_id)
		{
			all_ratings.push_back(r);
		}
	}
	return all_ratings;
}
std::vector<Song> Context::get_n_ordered_songs(size_t _count)
{
	sort(songs.begin(),songs.end(), [](Song& s1, Song& s2)
		{
			return s1.get_name() < s2.get_name();
		});

	auto end = std::next(songs.begin(), std::min(_count, songs.size()));
	std::vector<Song> result(songs.begin(), end);
	return result;
}

std::vector<Song> Context::get_songs_by_list_of_genres(std::vector<std::string> _genres)
{
	std::vector<Song> s;
	std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		{
			return std::find(_genres.begin(),_genres.end(), _song.get_genre()) != _genres.end(); 
		});
	return s;
}
std::vector<Song> Context::get_songs_except_genres(std::vector<std::string> _genres)
{
	std::vector<Song> s;
	std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		{
			return std::find(_genres.begin(), _genres.end(), _song.get_genre()) == _genres.end(); 
		});
	return s;
}
std::vector<Song> Context::get_songs_by_rating(float _rating)
{
	 std::vector<Song> s;
	 std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		 {
			 return _song.get_rating() >= _rating; 
		 });
	 sort(s.begin(), s.end(), [](Song& s1, Song& s2)
		 {
			 return s1.get_rating() > s2.get_rating();
		 });
	 return s;
}
std::vector<Song> Context::get_songs_from_year(int _year)
{
	std::vector<Song> s;
	std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		{
			return _song.get_release_year() == _year; 
		});
	return s;
}
std::vector<Song> Context::get_songs_before_year(int _year)
{
	std::vector<Song> s;
	std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		{
			return _song.get_release_year() < _year; 
		});
	return s;
}
std::vector<Song> Context::get_songs_after_year(int _year)
{

	std::vector<Song> s;
	std::copy_if(songs.begin(), songs.end(), std::back_inserter(s), [&](Song _song) 
		{
			return _song.get_release_year() > _year; 
		});
	return s;
}
std::vector<std::string> Context::get_all_playlists_by_cretor_id(std::string _crteator_id)
{
	std::vector<std::string> playlists_name;
	for (Playlist& p : playlists)
	{
		if (p.get_creator_id()==_crteator_id)
		{
			playlists_name.push_back(p.get_name());
		}
	}
	return playlists_name;
}
//

//methods required by the json library
	//Song
void to_json(json& j, const Song& s) 
{
	j = json{
		{"id", s.get_id()},
		{"artist", s.get_artist()},
		{"name", s.get_name()},
		{"genre", s.get_genre()},
		{"rating", s.get_rating()},
		{"album", s.get_album()},
		{"release year",s.get_release_year()},
	};
}
void from_json(const json& j, Song& s) 
{
	s.set_id(j.at("id"));
	s.set_artist(j.at("artist"));
	s.set_name(j.at("name"));
	s.set_genre(j.at("genre"));
	s.set_rating(j.at("rating"));
	s.set_album(j.at("album"));
	s.set_release_year(j.at("release year"));
}

	//Playlist
void to_json(json& j, const Playlist& p) 
{
	j = json {
		{"creator id", p.get_creator_id()},
		{"songs", p.get_songs()},
		{"name", p.get_name()}
	};
}
void from_json(const json& j, Playlist& p) 
{
	p.set_creator(j.at("creator id"));
	p.set_name(j.at("name"));
	p.set_songs((j.at("songs")));
	
}

	//User
void to_json(json& j, const User& u)
{
	j = json{
		{"username", u.get_username()},
		{"password", u.get_password()},
		{"fullname", u.get_fullname()},
		{"birthday", u.birthday_to_string()},
		{"favorite genres", u.get_favorite_genres()},
		{"id",u.get_id()}
	};
}
void from_json(const json& j, User& u) 
{
	u.set_username(j.at("username"));
	u.set_password(j.at("password"));
	u.set_fullname(j.at("fullname"));
	u.set_birthday(j.at("birthday"));
	u.set_favorite_genres(j.at("favorite genres"));
	u.set_id(j.at("id"));
}

	//Rating
void to_json(json& j, const Rating& r) 
{
	j = json{
		{"User_id", r.user_id},
		{"Song_id", r.song_id},
		{"Rating",r.rating}
	};
}
void from_json(const json& j, Rating& r) 
{
	r.user_id=j.at("User_id");
	r.song_id=j.at("Song_id");
	r.rating=j.at("Rating");
}
//

bool Context::available_username(std::string _username)
{
	User* user = get_user_by_username(_username);
	return user->get_username().empty();
}
bool Context::login_validation(std::string _username, std::string _password)
{
	if (available_username(_username))
		return false;

	User* user = get_user_by_username(_username);
	std::string result = user->get_password();
	std::string candidate = Chocobo1::SHA3_512()
		.addData(_password.c_str(), _password.length())
		.finalize()
		.toString();

	return result == candidate;
}
bool Context::rated_song(std::string _user_id, std::string _song_id)
{
	//maybe the rating should me modified
	for (auto r : ratings)
	{
		if (r.user_id==_user_id && r.song_id == _song_id)
		{
			return true;
		}
	}
	return false;


}

bool Context::song_exists(Song _song)
{
	for (auto s:songs)
	{
		if (s==_song)
		{
			return true;
		}
	}
	return false;
}
bool Context::playlist_exists(Playlist _playlist)
{
	for (Playlist p : playlists)
	{
		if (p == _playlist)
		{
			return true;
		}
	}
	return false;
}

bool Context::add_user(User _user)
{
	if (available_username(_user.get_username()))
	{
		users.push_back(_user);
		return true;
	}
		return false;
	
}
bool Context::add_song(Song _song)
{
	if (!song_exists(_song))
	{
		songs.push_back(_song);
		return true;
	}
	return false;
}
bool Context::add_playlist(Playlist _playlist)
{
	if (!playlist_exists(_playlist))
	{
		playlists.push_back(_playlist);
		return true;
	}
	return false;
}
bool Context::add_rating(std::string _user_id, std::string _song_id,float _rating)
{
	
	if (rated_song(_user_id,_song_id))
	{
		return false; // za sega
	}
	Rating r{ _user_id,_song_id,_rating };
	ratings.push_back(r);
	return true;
}

//working with .json files
void Context::Serialization()
{

	std::ifstream in("Users.json");
	std::string s;
	while (in)
	{
		std::string line;
		std::getline(in, line);
		s.append(line);
	}
	in.close();
	if (!s.empty())
	{
		json = json::parse(s);
		users = json.get<std::vector<User>>();
		json.clear();
	}
	//
	in.open("Songs.json");
	s.clear();
	while (in)
	{
		std::string line;
		std::getline(in, line);
		s.append(line);
	}
	in.close();
	if (!s.empty())
	{
		json = json::parse(s);
		songs = json.get<std::vector<Song>>();
		json.clear();

	}
	//
	in.open("Playlists.json");
	s.clear();
	while (in)
	{
		std::string line;
		std::getline(in, line);
		s.append(line);
	}
	in.close();
	if (!s.empty())
	{
		json = json::parse(s);
		playlists = json.get<std::vector<Playlist>>();
	}
	//
	in.open("Ratings.json");
	s.clear();
	while (in)
	{
		std::string line;
		std::getline(in, line);
		s.append(line);
	}
	in.close();
	if (!s.empty())
	{
		json = json::parse(s);
		ratings = json.get<std::vector<Rating>>();
	}
}
void Context::Deserialization()
{
	json.clear();
	json = users;
	std::ofstream out("Users.json");
	out << json.dump(formating_spaces);
	out.close();

	json.clear();
	out.open("Songs.json");
	json = songs;
	out << json.dump(formating_spaces);
	out.close();

	json.clear();
	out.open("Playlists.json");
	json = playlists;
	out << json.dump(formating_spaces);
	out.close();

	json.clear();
	out.open("Ratings.json");
	json = ratings;
	out << json.dump(formating_spaces);
	out.close();

	json.clear();

}
//

