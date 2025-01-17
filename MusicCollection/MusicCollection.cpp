#include <iostream>
#include <sstream>
#include "Repl.h"
#include <locale>

/// \mainpage Music Collection
/// <a href="https://github.com/damianivanov/CS-SDP/tree/master/MusicCollection">Project Repository</a>
/// \section mainIdea Main Idea
/// The main Idea of this project is to complete operations for the adding,storing and changing information about
/// Songs, Users and their generated by certain criteria, Playlists. The information is stored in JSON files, which makes it possible for using saved Users and 
/// Songs, between the different sessions. The application at this stage, it's console command interpreter.
/// 
/// \section requirments Project requirments
///   - Every User should have: 
///         - Username
///         - Password  
///         - Fullname 
///         - Birthday
///         - Favorite genres
///         - Stored Playlists
/// 
///   - Every Song should have: 
///         - Name  
///         - Artist  
///         - Album 
///         - Release year
///         - Genre
///         - Rating
/// 
/// \section functionality Functioality
/// \subsection user User 
/// - Registration
/// - Login
/// - User Info
///
/// \subsubsection changing_users Changing Users info
///  - Change favorite genres
///      -# add
///      -# remove
///  - Change fullname
///  - Change username
///  - Change password
///  - Change birthday
/// 
/// \subsection songs Song
/// - Add Song
/// - Rate Song
/// 
/// \subsection playlists Playlist
/// 
///   \subsubsection Generating
///     - Generate playlist of Songs by list of criterias and capacity, combined with logical operators AND, OR. Criterias can be one of the following:
///        -# Rating, bigger than given value
///        -# Including or Excluding a set of genres
///        -# Only from the favorite genres of the current logged User
///        -# From/After/Before a given year
///        -# All Songs in the database
/// 
/// \subsubsection w_w_playlists Working with playlists
///     - Save generated Playlist by name
///     - Load Playlist from the database
///     - Printing information about every Song in the Playlist
///     - Printing all of the Playlists for the logged User
/// 
/// 
/// \section usedLibraries Used Libraries
///     - <a href="https://github.com/nlohmann/json">Json</a> - This is a library which makes it easy to deserialize and serialize objects in json format and vice versa.
///     
///    All the library needs are:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    to_json(json& j, const Object& o); 
///    from_json(const json& j, Object& o);
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///    
///    In to_json(json& j, const Object& o) method, the way that the object is converted to string(json), is fully managed by the programmer, in format:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    j = json{
///		{"property1", o.property1()}, // where the keys("property1","property2","property3") have to be the same as in from_json()
///		{"property2", o.property2()},
///		{"property3", o.property3()}}
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// 
///    In from_json(const json& j, const Object& o) method, the way that the object is converted from string(json), is fully managed by the programmer, in format:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    p.property1(j.at("property1"));
///    p.property2(j.at("property2"));
///    p.property3((j.at("property3"))); 
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
///    And after that the serializiation is simple as:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    std::ofstream out("File.json");
///	   out << json.dump(formating_spaces);
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///    And the deserialization:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    std::string file_content;
///    json = json::parse(file_content);
///    std::vector<Object> = json.get<std::vector<Object>>();
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///     - <a href="https://github.com/Chocobo1/Hash">Hashing</a>
/// 
///    The function SHA3_512() is a hashing function used like:
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
///    std::string hashed_string = Chocobo1::SHA3_512()
///                   .addData(original_string.c_str(), original_string.length())
///                   .finalize()
///                   .toString();
///    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	Repl program;
	program.run();
	return 0;
}


