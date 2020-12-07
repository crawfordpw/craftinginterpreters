///////////////////////////////////////////////////////////////////////////////
//
//	File: Scanner.cpp
//
//	The Scanner is responsible for stepping through the source one character
//  at a time, pushing valid tokens to a vector. A token is made up of a lexeme,
//  which is the smallest group of character sequences that represent something,
//  among with other data, such as the line it was found on.
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "Scanner.hpp"

Scanner::Scanner(const std::string &lSource, Logger *lLogger) : mSource(lSource),
                    mLogger(lLogger), mStart(0), mCurrent(0), mLine(1) {}

//-----------------------------------------------------------------------------
//
//	The scanner works its way through the source code, adding tokens to a
//  vector until it runs out of characters. Then it appends one final
//  “end of file” token.
//
//-----------------------------------------------------------------------------
std::vector<Token> Scanner::ScanTokens()
{
    while(!IsAtEnd())
    {
        mStart = mCurrent;
        ScanToken();
    }
    mTokens.push_back(Token(TokenType::ENDFILE, "", "", mLine));

    return mTokens;
}

bool Scanner::IsAtEnd()
{
    return mCurrent >= mSource.length();
}

// Consumes the next character in the source file and returns it
char Scanner::Advance()
{
    mCurrent++;
    return mSource.at(mCurrent - 1);
}

void Scanner::AddToken(TokenType lType)
{
    AddToken(lType, "");
}

void Scanner::AddToken(TokenType lType, const std::string &lLiteral)
{
    std::string lLexeme = mSource.substr(mStart, mCurrent - mStart);
    mTokens.push_back(Token(lType, lLexeme, lLiteral, mLine));
}

void Scanner::ScanToken()
{
    char c = Advance();

    switch(c)
    {
        // single character lexemes
        case '(': AddToken(LEFT_PAREN);   break;
        case ')': AddToken(RIGHT_PAREN);  break;
        case '{': AddToken(LEFT_BRACE);   break;
        case '}': AddToken(RIGHT_BRACE);  break;
        case ',': AddToken(COMMA);        break;
        case '.': AddToken(DOT);          break;
        case '-': AddToken(MINUS);        break;
        case '+': AddToken(PLUS);         break;
        case ';': AddToken(SEMICOLON);    break;
        case '*': AddToken(STAR);         break;

        default:
            mLogger->Error(mLine, "Unexpected character.");
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//	 End of Scanner.cpp
///////////////////////////////////////////////////////////////////////////////
