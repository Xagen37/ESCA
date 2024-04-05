/// @file common.cpp
///
/// @brief Файл в котором храняться общие данные для всего проекта
///
/// @author alexust27
/// Contact: ustinov1998s@gmail.com
///

#include <string>

#include "common.h"

void CommonStorage::SetIncludeDirs( const std::vector<std::string> &inclPaths )
{
    includeDirs = inclPaths;
}

bool CommonStorage::InIncludeDirs( const std::string &file )
{
    for( const auto &path: includeDirs )
    {
        if( file.find(path) != std::string::npos )
        {
            return true;
        }
    }
    return false;
}

bool CommonStorage::AddAnalyzeFile( const std::string &file )
{
    if( IsAlreadyAnalyzed(file))
    {
        return false;
    }
    analyzeFile = file;
    analyzedFiles.insert(file);
    return true;
}

bool CommonStorage::IsAlreadyAnalyzed( const std::string &file )
{
//    if( file == analyzeFile )
//    {
//        return false;
//    }
    return analyzedFiles.count(file);
}

