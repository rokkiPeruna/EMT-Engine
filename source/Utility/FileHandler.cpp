#include <Utility/FileHandler.hpp>

//All common definitions in this file

namespace jej
{

    std::vector<char>& FileHandler::GetReadDataRef()
    {
        return m_fileContents;
    }
    //////////////////////////////////////////


    const std::vector<char>& FileHandler::GetReadDataRef() const
    {
        return m_fileContents;
    }
    //////////////////////////////////////////


    std::vector<char> FileHandler::GetReadData()
    {
        return m_fileContents;
    }
    //////////////////////////////////////////


}