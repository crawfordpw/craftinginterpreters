///////////////////////////////////////////////////////////////////////////////
//
//	File: Scanner.hpp
//
//	A header file for the Scanner class
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "Logger.hpp"
#include "Token.hpp"

#ifndef SCANNER_HPP
#define SCANNER_HPP

class Scanner
{
    public:

        Scanner(const std::string &lSource, Logger *lLogger);

        std::vector<Token> ScanTokens();

    private:

        const std::string   mSource;
        Logger              *mLogger;
        unsigned int        mStart;
        unsigned int        mCurrent;
        unsigned int        mLine;
        std::vector<Token>  mTokens;

        bool IsAtEnd();
        void ScanToken();
        char Advance();
        void AddToken(TokenType lType);
        void AddToken(TokenType lType, const std::string &lLiteral);
};

#endif

///////////////////////////////////////////////////////////////////////////////
//	 End of Scanner.hpp
///////////////////////////////////////////////////////////////////////////////
