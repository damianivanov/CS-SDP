#pragma once
#include <string>
#include "MusicPlayer.h"

class Repl
{
public:
	Repl();
	~Repl();
	void repl();

private:
	MusicPlayer* mp;

	void help();
};
