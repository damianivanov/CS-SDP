#include <iostream>
#include <sstream>
#include "Repl.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    //Playlist p;
    //std::vector<Song> s;
    //Song s1("id","artist","name","rap","nz",2018,3.6);
    //s.push_back(s1);
    //p.set_songs(s);
    Repl program;
    program.repl();
    return 0;
}


