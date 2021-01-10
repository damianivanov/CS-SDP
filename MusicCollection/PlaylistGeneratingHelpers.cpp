#include <algorithm>
#include "Song.h"
#include <vector>

/// Merging two vectors of Songs with operator OR
/// 
/// New vector is combination of left hand side vector and songs from the right hand side vector 
/// ONLY if they are not in the result yet.
/// <param name="_l">left hand side vector of Songs</param>
/// <param name="_r">right hand side vector of Songs</param>
/// <returns>vector of Song</returns>
static std::vector<Song> merge_or(const std::vector<Song> _l, const std::vector<Song> _r)
{
	std::vector<Song> s(_l);
	std::copy_if(_r.begin(), _r.end(), std::back_inserter(s), [&](const Song _song)
		{
			return std::find_if(_l.begin(), _l.end(), [&](const Song s)
				{
					return s.get_id() == _song.get_id();
				}) == _l.end();
		});
	return s;
}

/// Merging two vectors of Songs with operator AND
/// 
/// The result is vector of Songs that are in both left and right hand side vector
/// <param name="_l">left hand side vector of Songs</param>
/// <param name="_r">right hand side vector of Songs</param>
/// <returns>vector of Song</returns>
static std::vector<Song> merge_and(const std::vector<Song> _l, const std::vector<Song> _r)
{
	std::vector<Song> s;
	std::copy_if(_l.begin(), _l.end(), std::back_inserter(s), [&](const Song _song)
		{
			return std::find_if(_r.begin(), _r.end(), [&](const Song s) { return s.get_id() == _song.get_id(); }) != _r.end();
		});
	return s;
}
