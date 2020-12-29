#include <iostream>
#include <sstream>
#include "Repl.h"
#include <locale>

using json = nlohmann::json;

int main()
{
    Repl program;
    program.repl();
    return 0;
}


