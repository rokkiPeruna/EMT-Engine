#ifndef JEJ_FILEHANDLER_ANDROID_HPP
#define JEJ_FILEHANDLER_ANDROID_HPP

//All Android-specific definitions in this file

#ifdef __ANDROID__

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>

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
        m_app(nullptr)
    {
        m_app = new android_app(*(AndroidAppState::m_AppState));
    }
    //////////////////////////////////////////


    FileHandler::~FileHandler()
    {
        if (m_app)
        {
            delete m_app;
            m_app = nullptr;
        }

    }
    //////////////////////////////////////////


    bool FileHandler::Read(const std::string& name, const unsigned int length)
    {

        AAsset* file = AAssetManager_open(m_app->activity->assetManager, name.c_str(), AASSET_MODE_BUFFER);

        if (!file)
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to open file: ", name);
            return false;
        }

        auto size = AAsset_getLength(file);
        if (length != 0u && length <= size)
            size = length;
        if (length > size)
            Messenger::Add(Messenger::MessageType::Warning, "File length too large:", length, "File size: ", size, "Suppressing");

        m_fileContents.resize(size + 1u);
        int result = AAsset_read(file, &m_fileContents[0], size);

        if (result < 0)
            Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", name);

        AAsset_close(file);

        return true;
    }
    //////////////////////////////////////////


    bool FileHandler::Write(const std::string& name)
    {
        Messenger::Add(Messenger::MessageType::Error, "Write-method needs to be written for android");
        //TODO: Android problems//Messenger::Add(Messenger::MessageType::Error, "Write-method needs to be written for android");
        return true;
    }
    //////////////////////////////////////////


    bool FileHandler::_accessFile(const std::string& p_name, const bool p_createFile)
    {
        //TODO: Needs definition on android
        JEJ_ASSERT(false, "Needs definition on android");
        return false;
    }

}

#endif

#endif