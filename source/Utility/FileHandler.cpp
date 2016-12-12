#include <Utility/FileHandler.hpp>

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include <External/STB/stb_truetype.h>

#define STB_IMAGE_IMPLEMENTATION
#include <External/STB/stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <External/STB/stb_image_resize.h>

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