#include "DatabaseContext.h"
//getters like methods

User Context::get_user_by_id(std::string _id)
{
	User u;
	for (auto user : users)
	{
		if (user.get_id() == _id)
		{
			return user;
		}
	}
	return u;
}
User* Context::get_user_by_username(std::string _username)
{
	User u;
	for (User& user : users)
	{
		if (user.get_username()==_username)
		{
			return &user;
		}
	}
	return &u;
}
//

//methods required by the json library
	

	//Song
void to_json(json& j, const Song& s) {
	j = json{
		{"artist", s.get_artist()},
		{"name", s.get_name()},
		{"genre", s.get_genre()},
		{"rating", s.get_rating()},
		{"album", s.get_album()},
		{"release year",s.get_release_year()},
	};
}
void from_json(const json& j, Song& s) {
	s.set_artist(j.at("artist"));
	s.set_name(j.at("name"));
	s.set_genre(j.at("genre"));
	s.set_rating(j.at("rating"));
	s.set_album(j.at("album"));
	s.set_release_year(j.at("release year"));
}

	//Playlist
void to_json(json& j, const Playlist& p) {
	j = json {
		{"creator", p.get_creator()},
		{"songs", p.get_songs()},
		{"name", p.get_name()}
	};
}
void from_json(const json& j, Playlist& p) {
	p.set_creator("creator");
	p.set_name(j.at("name"));
	p.set_songs((j.at("songs")));
	
}

	//User
void to_json(json& j, const User& u) {
	j = json{
		{"username", u.get_username()},
		{"password", u.get_password()},
		{"fullname", u.get_fullname()},
		{"birthday", u.birthday_to_string()},
		{"favorite genres", u.get_favorite_genres()},
		{"id",u.get_id()},
		{"Playlist", u.get_playlists()}
	};
}
void from_json(const json& j, User& u) {
	u.set_username(j.at("username"));
	u.set_password(j.at("password"));
	u.set_fullname(j.at("fullname"));
	u.set_birthday(j.at("birthday"));
	u.set_favorite_genres(j.at("favorite genres"));
	u.set_id(j.at("id"));
	//TODO::Playlists
}
//

bool Context::available_username(std::string _username)
{
	User* user = get_user_by_username(_username);
	return user->get_username() == "";
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
bool Context::add_user(User _user)
{
	if (available_username(_user.get_username()))
	{
		users.push_back(_user);
		return true;
	}
		return false;
	
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
}
//

