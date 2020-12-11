#include <iostream>
#include <sstream>
#include "MusicPlayer.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    MusicPlayer mp;
    //mp.Register();
    mp.login(); 
    /*mp.get_logged_user()->add_favorite_genre("rap");
    mp.get_logged_user()->add_favorite_genre("pop");
    mp.get_logged_user()->add_favorite_genre("chill");
    mp.get_logged_user()->add_favorite_genre("rap");
    mp.get_logged_user()->remove_favorite_genre("rap");*/
    //mp.get_logged_user()->set_fullname("Damian Ivanov");
    //mp.creating_song();
    mp.rate_song();
    //mp.add_genre();
    //mp.remove_genre();
   
  
    //u1.add_playlist(p1);
    }


