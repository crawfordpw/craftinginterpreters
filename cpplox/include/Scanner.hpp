///////////////////////////////////////////////////////////////////////////////
//
//	File: Scanner.hpp
//
//	A header file for the Scanner class
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <unordered_map>

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

        const std::string                       mSource;
        Logger                                  *mLogger;
        unsigned int                            mStart;
        unsigned int                            mCurrent;
        unsigned int                            mLine;
        std::vector<Token>                      mTokens;
        std::unordered_map<std::string, TokenType> mReservedWords;

        bool IsAtEnd();
        char Advance();
        void AddToken(TokenType lType);
        void AddToken(TokenType lType, const std::string &lLiteral);
        bool Match(char lExpected);
        char Peek();
        char PeekNext();
        void String();
        bool IsDigit(char c);
        void Number();
        bool IsAlpha(char c);
        bool IsAlphaNumeric(char c);
        void Identifier();
        void ScanToken();
};

#endif

///////////////////////////////////////////////////////////////////////////////
//	 End of Scanner.hpp
///////////////////////////////////////////////////////////////////////////////
