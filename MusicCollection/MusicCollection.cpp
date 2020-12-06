#include <iostream>
#include <sstream>
#include "DatabaseContext.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    Context db;
    db.Serialization();
    db.Deserialization();
   /* User u1("damian.iv", "pass1", "Damian Ivanov", std::vector<std::string> {"pop", "rap", "slow"}, std::vector<Playlist> {}, "30/07/1998");
    auto users = std::vector<User*>();
    users.push_back(&u1);

    Song BOP("DaBaby", "BOP", "rap", 3.5, "Kirk", 2020);
    Song BOPCopy(BOP);

    Playlist p1;
    p1.add_song(&BOP);
    p1.set_name("DaBaby");
    u1.add_playlist(p1);
    std::cout<<u1.get_playlists().front().get_songs().front()->get_name();*/
}


