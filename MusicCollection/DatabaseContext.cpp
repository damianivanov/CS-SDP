#include "DatabaseContext.h"

User& Context::get_user_by_id(std::string _id)
{
	auto it = std::find_if(get_all_users().begin(), get_all_users().end(), [&_id](const User& user) {return user.get_id() == _id; });
	User user;
	if (it != get_all_users().end())
	{
		user = *it;
		auto index = std::distance(get_all_users().begin(), it);
	}
	return user;
}
User& Context::get_user_by_username(std::string _username)
{
	auto it = std::find_if(get_all_users().begin(), get_all_users().end(), [&_username](const User& user) {return user.get_username() == _username; });
	User user;
	if (it != get_all_users().end())
	{
		user = *it;
		auto index = std::distance(get_all_users().begin(), it);
	}
	return user;
}
bool Context::validate_user(std::string _username, std::string _password)
{
	User user = get_user_by_username(_username);
	if (user.get_username() == "")
		return false;

	std::string result = user.get_password();
	std::string candidate = Chocobo1::SHA3_512()
		.addData(_password.c_str(), _password.length())
		.finalize()
		.toString();

	return result == candidate;
}
void to_json(json& j, const User& u) {
	j = json{
		{"username", u.get_username()},
		{"password", u.get_password()},
		{"fullname", u.get_fullname()},
		{"birthday", u.birthday_to_string()},
		{"favorite genres", u.get_favorite_genres()},
		{"id",u.get_id()},
		//{"Playlist", u.get_playlists()} //need to_json, from_json
	};
}
void from_json(const json& j, User& u) {
	u.set_username(j.at("username"));
	u.set_password(j.at("password"));
	u.set_fullname(j.at("fullname"));
	u.set_birthday(j.at("birthday"));
	u.set_favorite_genres(j.at("favorite genres"));
	u.set_id(j.at("id"));
}
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
		
	json = json::parse(s);
	users = json.get<std::vector<User>>();
}

void Context::Deserialization()
{
	json.clear();
	json = users;
	std::ofstream out("Users.json");
	out << json.dump(formating_spaces);
	out.close();
}

