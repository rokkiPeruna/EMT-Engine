#include <Utility/FileHandler.hpp>

#include <Core/Settings.hpp>
#include <EntityComponentSys/Components/TextureComponent.hpp>
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

#ifdef _WIN32

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
        if (!_accessFile(p_name, false))
            return false;

        auto size = GetFileSize(m_fileHandle, NULL);

        unsigned char* buf = new unsigned char[size];

        stbtt_InitFont(&p_font->fontInfo, buf, p_font->fontOffset);

        std::memcpy(&p_font->fontData, &buf, size);

        delete[] buf;

        return true;

    }
    //////////////////////////////////////////


    bool FileHandler::ReadImage(TextureComponent* p_component)
    {
        JEJ_ASSERT(!p_component->m_textureData.imageName.empty(), "No texture name given");

        const std::string imagePath = "Textures/" + p_component->m_textureData.imageName;
        if (!_accessFile(imagePath, false))
        {
            Messenger::Add(Messenger::MessageType::Error, "Texture could not be read");
            return false;
        }

        //Used for copying data
        p_component->m_textureData.imageDataSize = GetFileSize(m_fileHandle, NULL);
        //Release handle so that stb can access the file
        _releaseHandle();

        //Load image
        p_component->m_completeImageData = stbi_load(
            std::string(settings::rootPath + "Resources/" + imagePath).c_str(),
            &p_component->m_textureData.wholeImageSize.x,
            &p_component->m_textureData.wholeImageSize.y,
            &p_component->m_textureData.imageOffset,
            0);

        if (p_component->m_completeImageData)
            return true;

        return false;
    }
    //////////////////////////////////////////


    bool FileHandler::ReadSingleImage(
        TextureComponent::TextureData* p_data,
        const unsigned char* p_wholeImageData,
        const unsigned int p_index)
    {
        const unsigned int singleImageX = p_data->wholeImageSize.x / p_data->imageCount;
        const unsigned int singleImageY = p_data->wholeImageSize.y / p_data->imageCount;

        //TODO: What do these things do?
        const unsigned int outStrideBytes = 0u;
        const unsigned int outChannelCount = 0u;

        stbir_resize_uint8(
            p_wholeImageData,
            p_data->wholeImageSize.x,
            p_data->wholeImageSize.y,
            p_data->imageOffset,
            p_data->displayImage,
            singleImageX,
            singleImageY,
            outStrideBytes,
            outChannelCount);

        if (p_data->displayImage)
            return true;

        return false;
    }
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

#elif defined ANDROID

    FileHandler::FileHandler(android_app* app) :
        m_fileContents(),
        m_app(new android_app(*(app)))
    {

    }
    //////////////////////////////////////////


    FileHandler::~FileHandler()
    {
        if (m_app)
            delete m_app;
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
    }
    //////////////////////////////////////////

    bool FileHandler::_accessFile(const std::string& p_name, const bool p_createFile)
    {
        //TODO: Needs definition on android
        JEJ_ASSERT(false, "Needs definition on android");
        return false;
    }

#endif



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