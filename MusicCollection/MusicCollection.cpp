#include <iostream>
#include <sstream>
#include "Repl.h"
#include <locale>

/// \mainpage Music Collection
/// System for music collection with supported users and generating playlists of songs by criterias.
/// 
/// \section functionality Functioality
/// 
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
int main()
{
    Repl program;
    program.run();
    return 0;
}


