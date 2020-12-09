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
#include <sstream>
#include <vector>

#include "Logger.hpp"
#include "Scanner.hpp"
#include "Token.hpp"

// forward declarations
void runFile(const char *lFilename);
void runPrompt();
void run(const std::string &lLine, Logger *lLogger);

//-----------------------------------------------------------------------------
//
//	The main function of the interpreter supports two ways of running code.
//      1. Ran with no arguments. It drops you into a prompt where you can
//          enter and execute code one line at a time.
//      2. Ran with one argument to a single file. It reads and executes.
//
//-----------------------------------------------------------------------------
int main(int argc, const char* argv[])
{ 
    switch (argc)
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
    Logger lLogger;

    std::ifstream ifs(lFilename, std::ios::in);
    if (!ifs.fail())
    {
        std::ostringstream contents;
        contents << ifs.rdbuf();
        ifs.close();
        run(contents.str(), &lLogger);

        if (lLogger.mHadError) exit(65);
    }
    else
    {
        std::cout << "Error opening file: " << lFilename;
        exit(66);
    }
}

void runPrompt()
{
    Logger      lLogger;
    std::string lLine;

    while (1)
    {
        std::cout << "> ";
        
        if (!std::getline(std::cin, lLine).fail())
        {
            std::cout << "\n";
            break;
        }
        run(lLine, &lLogger);
        lLogger.mHadError = false;
    }
}

void run(const std::string &lSource, Logger *lLogger)
{
    Scanner Scanner(lSource, lLogger);
    std::vector<Token> tokens = Scanner.ScanTokens();

    for (Token token : tokens)
    {
        std::cout << token.mType << " " << token.mLexeme << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
//	 End of main.cpp
///////////////////////////////////////////////////////////////////////////////
