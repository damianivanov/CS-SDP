#include <iostream>
#include <sstream>
#include "MusicPlayer.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    MusicPlayer mp;
    //mp.Register();
    mp.Login(); 
    mp.get_logged_user()->add_favorite_genre("rap");
    mp.get_logged_user()->add_favorite_genre("pop");
    mp.get_logged_user()->add_favorite_genre("chill");
    mp.get_logged_user()->add_favorite_genre("rap");
    mp.get_logged_user()->remove_favorite_genre("rap");
    ;
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
    //std::cout << mp.get_logged_user()->get_favorite_genres()[0] << std::endl;
    }

//TODO:: Song should have print method
//TODO:: Playlist should have print_all songs method


