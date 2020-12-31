#pragma once
#include <string>
#include "MusicPlayer.h"

class Repl
{
public:
	/// allocating memory for mp-Music Player
	Repl();
	/// deleting the allocated memory for mp
	~Repl();
	/// The process of taking users input and evaluating it,until exit command is received
	void run();

private:
	/// Pointer to Music Player instance
	MusicPlayer* mp;
private:
	/// Print function for every supported command and information what it does.
	void help();
};
