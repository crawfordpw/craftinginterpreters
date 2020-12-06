///////////////////////////////////////////////////////////////////////////////
//
//	File: Scanner.hpp
//
//	A header file for the Scanner class
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "Token.hpp"

#ifndef SCANNER_HPP
#define SCANNER_HPP

class Scanner
{
    public:

        Scanner(const std::string &lLine) : mLine(lLine) {}
        std::vector<Token> ScanTokens();

    private:
    
        const std::string mLine;
        std::vector<Token> mTokens;

};

#endif

///////////////////////////////////////////////////////////////////////////////
//	 End of Scanner.hpp
///////////////////////////////////////////////////////////////////////////////