///////////////////////////////////////////////////////////////////////////////
//
//	File: main.cpp
//
//	This is the project's main entry point
//
///////////////////////////////////////////////////////////////////////////////

// includes
#include <iostream>
#include <string>
#include <fstream>

// forward declarations
void runFile(const char *lFilename);
void runPrompt();
void run(std::string lLine);

//-----------------------------------------------------------------------------
//
//	The main function of the interpreter supports two ways of running code.
//      1. Ran with no arguments; it drops you into a prompt where you can
//          enter and execute code one line at a time.
//      2. Ran with one argument to a single file; it reads and executes.
//
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{ 
    switch(argc)
    {
        case 1:
            runPrompt();
            break;
        case 2:
            runFile(argv[1]);
            break;
        default:
            std::cout << "Usage: cpplox [script]";
            exit(64);
    }  
    return 0;
}

void runFile(const char *lFilename)
{
    std::string lLine;
}

void runPrompt()
{
    std::string lLine;
    while(1)
    {
        std::cout << "> ";
        
        if(!std::getline(std::cin, lLine))
        {
            std::cout << "\n";
            break;
        }
        run(lLine);
    }
}

void run(std::string lLine)
{

}

///////////////////////////////////////////////////////////////////////////////
//	 End of main.cpp
///////////////////////////////////////////////////////////////////////////////