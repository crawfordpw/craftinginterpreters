///////////////////////////////////////////////////////////////////////////////
//
//	File: Logger.cpp
//
//	A class for logging errors
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Logger.hpp"

Logger::Logger() : mHadError(false) {}

void Logger::Error(unsigned int lLine, const std::string &lMessage)
{
    Report(lLine, lMessage, "");
}

void Logger::Report(unsigned int lLine, const std::string &lMessage, const std::string &lWhere)
{
    std::cout << "[line " << lLine << "] Error" << lWhere << ": " << lMessage;
    mHadError = true;
}

///////////////////////////////////////////////////////////////////////////////
//	 End of Logger.cpp
///////////////////////////////////////////////////////////////////////////////
