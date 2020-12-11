///////////////////////////////////////////////////////////////////////////////
//
//	File: Scanner.cpp
//
//	The Scanner is responsible for stepping through the source one character
//  at a time, pushing valid tokens to a vector. A token is made up of a lexeme,
//  which is the smallest group of character sequences that represent something.
//  A token contains a lexeme among other data, such as the line it was found on.
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "Scanner.hpp"

Scanner::Scanner(const std::string &lSource, Logger *lLogger) : mSource(lSource),
                    mLogger(lLogger), mStart(0), mCurrent(0), mLine(1)
{
    mReservedWords =
    {
        {"and",    TokenType::AND},
        {"class",  TokenType::CLASS},
        {"else",   TokenType::ELSE},
        {"false",  TokenType::FALSE},
        {"for",    TokenType::FOR},
        {"fun",    TokenType::FUN},
        {"if",     TokenType::IF},
        {"nil",    TokenType::NIL},
        {"or",     TokenType::OR},
        {"print",  TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super",  TokenType::SUPER},
        {"this",   TokenType::THIS},
        {"true",   TokenType::TRUE},
        {"var",    TokenType::VAR},
        {"while",  TokenType::WHILE}
    };
}

//-----------------------------------------------------------------------------
//
//	The scanner works its way through the source code, adding tokens to a
//  vector until it runs out of characters. Then it appends one final
//  “end of file” token.
//
//-----------------------------------------------------------------------------
std::vector<Token> Scanner::ScanTokens()
{
    while (!IsAtEnd())
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

// Similar to Advance, but conditional based on the next char in source
bool Scanner::Match(char lExpected)
{
    if (IsAtEnd()) return false;
    if (mSource.at(mCurrent) != lExpected) return false;

    mCurrent++;
    return true;
}

// Similar to Advance, but doesn't consume the character. Lookahead by one.
char Scanner::Peek()
{
    if (IsAtEnd()) return '\0';
    return mSource.at(mCurrent);
}

// Similar to Peek, but allows for a lookahead of two after using Peek()
char Scanner::PeekNext()
{
    if (mCurrent + 1 >= mSource.length()) return '\0';
    return mSource.at(mCurrent + 1);
}

void Scanner::String()
{
    // Consume the string until corresponsing " is found.
    while (Peek() != '"' && !IsAtEnd())
    {
        if (Peek() == '\n')
        {
            mLine++;
        }
        Advance();
    }

    if (IsAtEnd())
    {
        mLogger->Error(mLine, "Unterminated string.");
        return;
    }

    // Found the closing "
    Advance();

    // Trim the surrounding quotes
    std::string lValue = mSource.substr(mStart + 1, mCurrent - mStart - 2);
    AddToken(TokenType::STRING, lValue);
}

bool Scanner::IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

// Get the whole number lexeme including the decimal parts, if any
void Scanner::Number()
{
    // Consume digits
    while (IsDigit(Peek())) Advance();

    // Look for a fractional part
    if (Peek() == '.' && IsDigit(PeekNext()))
    {
        //Consume the '.'
        Advance();

        // Continue consuming digits
        while (IsDigit(Peek())) Advance();
    }

    std::string lValue = mSource.substr(mStart, mCurrent - mStart);
    AddToken(TokenType::NUMBER, lValue);
}

bool Scanner::IsAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::IsAlphaNumeric(char c)
{
    return IsAlpha(c) || IsDigit(c);
}

void Scanner::Identifier()
{
    while (IsAlphaNumeric(Peek())) Advance();

    std::string lText = mSource.substr(mStart, mCurrent - mStart);
    auto lType = mReservedWords.find(lText);

    if (lType == mReservedWords.end())
    {
        AddToken(TokenType::IDENTIFIER);
    }
    else
    {
        AddToken(lType->second);
    }
}

void Scanner::ScanToken()
{
    char c = Advance();

    switch(c)
    {
        // single character lexemes
        case '(': AddToken(TokenType::LEFT_PAREN);   break;
        case ')': AddToken(TokenType::RIGHT_PAREN);  break;
        case '{': AddToken(TokenType::LEFT_BRACE);   break;
        case '}': AddToken(TokenType::RIGHT_BRACE);  break;
        case ',': AddToken(TokenType::COMMA);        break;
        case '.': AddToken(TokenType::DOT);          break;
        case '-': AddToken(TokenType::MINUS);        break;
        case '+': AddToken(TokenType::PLUS);         break;
        case ';': AddToken(TokenType::SEMICOLON);    break;
        case '*': AddToken(TokenType::STAR);         break;

        // operators
        case '!':
            AddToken(Match('=') ? TokenType::NOT_EQUAL : TokenType::NOT);
            break;
        case '=':
            AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        // "/" based lexemes
        case '/':
            if (Match('/'))
            {
                while (Peek() != '\n' && !IsAtEnd()) Advance(); 
            }
            else
            {
                AddToken(TokenType::SLASH);
            }
            break;
        
        // Ignore whitespace
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            mLine++;
            break;

        // Strings
        case '"':
            String();
            break;

        default:
            if (IsDigit(c))
            {
                Number();
            }
            else if (IsAlpha(c))
            {
                Identifier();
            }
            else
            {
                mLogger->Error(mLine, "Unexpected character.");
            }  
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//	 End of Scanner.cpp
///////////////////////////////////////////////////////////////////////////////
