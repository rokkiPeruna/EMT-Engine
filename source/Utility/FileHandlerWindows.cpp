#ifndef JEJ_FILEHANDLER_WINDOWS_HPP
#define JEJ_FILEHANDLER_WINDOWS_HPP

//All Windows-specific definitions in this file

#ifdef _WIN32

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>


#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include <External/STB/stb_truetype.h>

#define STB_IMAGE_IMPLEMENTATION
#include <External/STB/stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <External/STB/stb_image_resize.h>


namespace jej
{

    FileHandler::FileHandler() :
        m_fileContents(),
        m_fileHandle(nullptr)
    {

    }
    //////////////////////////////////////////


    FileHandler::~FileHandler()
    {
        _releaseHandle();
    }
    //////////////////////////////////////////


    bool FileHandler::Read(const std::string& name, const unsigned int length)
    {
        if (!_accessFile(name, false))
            return false;

        //Init
        LPDWORD dataRead = {};
        OVERLAPPED overlapped = {};
        const std::string filePath = settings::rootPath + "Resources/" + name;

        //Adjust how much data will be read, if necessary
        auto size = GetFileSize(m_fileHandle, NULL);
        if (length != 0u && length <= size)
            size = length;
        if (length > size)
            Messenger::Add(Messenger::MessageType::Warning, "File length too large:", length, "File size: ", size, "Suppressing");

        //Reserve invalid operation here
        m_fileContents.resize(size + 1u);

        //Read file
        if (FALSE == ReadFile(
            m_fileHandle,
            &m_fileContents[0],
            size,
            dataRead,
            &overlapped
            ))
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", filePath, getWinError());
            return false;
        }

        //Add string terminator if not present
        if (m_fileContents.back() != '\0')
            m_fileContents.emplace_back('\0');

        return true;
    }
    //////////////////////////////////////////


    bool FileHandler::ReadFontFile(const std::string& p_name, TextureComponent::Font* p_font)
    {
        if (!Read(p_name))
            return false;
        
        p_font->fontData = new unsigned char[m_fileContents.size() - 1u];
        
        for (unsigned int i = 0u; i < m_fileContents.size() - 1u; ++i)
            p_font->fontData[i] = m_fileContents[i];

        p_font->fontDataSize = m_fileContents.size() - 1u;
        stbtt_InitFont(&p_font->fontInfo, p_font->fontData, p_font->fontOffset);

        return true;
    }
    //////////////////////////////////////////


    bool FileHandler::ReadImage(TextureComponent::tempData* p_data)
    {
        JEJ_ASSERT(!p_data->name.empty(), "No texture name given");

        const std::string imagePath = "Textures/" + p_data->name;
        if (!_accessFile(imagePath, false))
        {
            Messenger::Add(Messenger::MessageType::Error, "Texture could not be read");
            return false;
        }

        //Used for copying data
        auto size = GetFileSize(m_fileHandle, NULL);
        //Release handle so that stb can access the file
        _releaseHandle();

        //Load image

        auto* data = stbi_load(
            std::string(settings::rootPath + "Resources/" + imagePath).c_str(),
            &p_data->x,
            &p_data->y,
            &p_data->offset,
            0);

        if (data)
        {
            for (unsigned int i = 0u; i < size; ++i)
                p_data->data.emplace_back(data[i]);
            stbi_image_free(data);


            return true;
        }


        return false;
    }
    //////////////////////////////////////////


    //  bool FileHandler::ReadSingleImage(
    //      TextureComponent::TextureData* p_data,
    //      const unsigned char* p_wholeImageData,
    //      const unsigned int p_index)
    //  {
    //      const unsigned int singleImageX = p_data->wholeImageSize.x / p_data->imageCount;
    //      const unsigned int singleImageY = p_data->wholeImageSize.y / p_data->imageCount;
    //
    //      //TODO: What do these things do?
    //      const unsigned int outStrideBytes = 0u;
    //      const unsigned int outChannelCount = 0u;
    //
    //      stbir_resize_uint8(
    //          p_wholeImageData,
    //          p_data->wholeImageSize.x,
    //          p_data->wholeImageSize.y,
    //          p_data->imageOffset,
    //          p_data->displayImage,
    //          singleImageX,
    //          singleImageY,
    //          outStrideBytes,
    //          outChannelCount);
    //
    //      if (p_data->displayImage)
    //          return true;
    //
    //      return false;
    //  }
    //////////////////////////////////////////


    bool FileHandler::Write(const std::string& p_name)
    {
        if (!_accessFile(p_name, true))
            return false;

        if (m_fileContents.empty())
        {
            Messenger::Add(Messenger::MessageType::Warning, "No data to write to file.");
            return false;
        }

        LPDWORD dataWritten = {};
        OVERLAPPED overlapped = {};

        if (FALSE == WriteFile(
            m_fileHandle,
            &m_fileContents[0],
            m_fileContents.size(),
            dataWritten,
            &overlapped
            ))
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to write to file: ", settings::rootPath + "Recources/" + p_name, getWinError());
            return false;
        }

        return true;

    }
    //////////////////////////////////////////


    bool FileHandler::_accessFile(const std::string& name, const bool createFile)
    {
        if (name.empty())
        {
            Messenger::Add(Messenger::MessageType::Error, "No file name specified to write to.");
            return false;
        }

        const std::string filePath = settings::rootPath + "Resources/" + name;

        m_fileHandle = CreateFile(
            LPCWSTR(std::wstring(filePath.begin(), filePath.end()).c_str()),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            createFile ? OPEN_ALWAYS : OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );

        if (m_fileHandle == INVALID_HANDLE_VALUE)
        {
            Messenger::Add(Messenger::MessageType::Warning, "Failed to ", createFile ? " create " : " open ", filePath, getWinError());
            return false;
        }
        return true;
    }
    //////////////////////////////////////////

    void FileHandler::_releaseHandle()
    {
        if (m_fileHandle)
        {
            CloseHandle(m_fileHandle);
            m_fileHandle = nullptr;
        }
    }

}


#endif

#endif
