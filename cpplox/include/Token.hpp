///////////////////////////////////////////////////////////////////////////////
//
//	File: Token.hpp
//
//	A header file for the Token class
//
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include "TokenType.hpp"

#ifndef TOKEN_HPP
#define TOKEN_HPP

class Token 
{
    public:

        TokenType       mType;
        std::string     mLexeme;
        std::string     mLiteral;
        unsigned int    mLine;

        Token() : mType(TokenType::INVALID), mLexeme(""), mLiteral(""), mLine(0) {}
        Token(TokenType lType, std::string lLexeme, std::string lLiteral, unsigned int lLine);

        std::string ToString();
};

#endif

///////////////////////////////////////////////////////////////////////////////
//	 End of Token.hpp
///////////////////////////////////////////////////////////////////////////////