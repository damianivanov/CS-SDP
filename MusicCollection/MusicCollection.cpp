#include <iostream>
#include <sstream>
#include "MusicPlayer.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    MusicPlayer mp;
   // mp.Register();
    mp.Login();
    //db.Serialization();
   
    /* User u1("damian.iv", "pass1", "Damian Ivanov", std::vector<std::string> {"pop", "rap", "slow"}, std::vector<Playlist> {}, "30/07/1998");
    auto users = std::vector<User>();
    users.push_back(u1);

    Song BOP("DaBaby", "BOP", "rap", 3.5, "Kirk", 2020);
    Song BOPCopy(BOP);

    Playlist p1;
    p1.add_song(BOP);
    p1.set_name("DaBaby");
    u1.add_playlist(p1);*/
    std::cout << "Hi" << std::endl;
    }

//TODO:: Song should have print method
//TODO:: Playlist should have print_all songs method


