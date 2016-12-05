#include <Utility/FileHandler.hpp>

#include <Core/Settings.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>
#include <Core/BaseStructs.hpp>

#include <EntityComponentSys/Components/TextureComponent.hpp>

namespace jej
{

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
    //#include <WinSock2.h>

    FileHandler::FileHandler() :
        m_fileContents(),
        m_fileHandle(nullptr)
    {

    }
    //////////////////////////////////////////


    FileHandler::~FileHandler()
    {
        if (m_fileHandle)
            CloseHandle(m_fileHandle);
    }
    //////////////////////////////////////////


    bool FileHandler::Read(const std::string& name, const unsigned int length)
    {
        if (!accessFile(name, false))
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

    bool FileHandler::ReadImage(TextureData* p_data)
    {
        JEJ_ASSERT(!p_data->imageName.empty(), "No texture name given");

        const std::string imagePath = "Textures/" + p_data->imageName;
        if (!accessFile(imagePath, false))
        {
            Messenger::Add(Messenger::MessageType::Error, "Texture could not be read");
            return false;
        }

        LPDWORD dataRead = {};
        OVERLAPPED overlapped = {};

        auto size = GetFileSize(m_fileHandle, NULL);

        std::vector<char> temp;
        //Reserve invalid operation here
        temp.resize(size + 1u);
        p_data->readImageData.resize(size + 1u);

        //Read file
        if (FALSE == ReadFile(
            m_fileHandle,
            &temp[0],
            size,
            dataRead,
            &overlapped
            ))
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", imagePath, getWinError());
            return false;
        }

        char value[4];
        unsigned int streamPos = 15u;

        //Width
        std::stringstream ss;
        for (unsigned char i = 0u; i < 4u; ++i, ++streamPos)
            ss << temp[streamPos];

        JEJ_ASSERT(false, "WIP, don't come here!");

        std::string asdf = ss.str();
        unsigned long int kek = std::stoul(asdf);
        p_data->singleImageSize.x = ntohl(kek);

        //Height
        for (unsigned char i = 0u; i < 4u; ++i, ++streamPos)
            value[i] = temp[streamPos];
        p_data->singleImageSize.y = ntohl(std::stoul(value));

        //ImageData
        std::memcpy(&p_data->readImageData[0], &temp[24u], temp.size() - 24u);

        return true;
    }


    bool FileHandler::Write(const std::string& name)
    {
        if (!accessFile(name, true))
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
            Messenger::Add(Messenger::MessageType::Error, "Failed to write to file: ", settings::rootPath + "Recources/" + name, getWinError());
            return false;
        }

        return true;

    }
    //////////////////////////////////////////


    bool FileHandler::accessFile(const std::string& name, const bool createFile)
    {
        if (name.empty())
        {
            Messenger::Add(Messenger::MessageType::Error, "No file name specified to write to.");
            return false;
        }

        const std::string filePath = settings::rootPath + "Resources/" + name;
        const std::wstring temp(filePath.begin(), filePath.end());

        m_fileHandle = CreateFile(
            LPCWSTR(temp.c_str()),
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


#elif defined __ANDROID__

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
            //TODO: Android problems
            //Messenger::Add(Messenger::MessageType::Error, "Failed to open file: ", name);
            return false;
        }

        auto size = AAsset_getLength(file);
        if (length != 0u && length <= size)
            size = length;
        if (length > size)
            //TODO: Android problems//Messenger::Add(Messenger::MessageType::Warning, "File length too large:", length, "File size: ", size, "Suppressing");

        m_fileContents.resize(size + 1u);
        int result = AAsset_read(file, &m_fileContents[0], size);

        if (result < 0)
            //TODO: Android problems//Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", name);

        AAsset_close(file);

        return true;
    }
    //////////////////////////////////////////

    bool FileHandler::Write(const std::string& name)
    {
        //TODO: Android problems//Messenger::Add(Messenger::MessageType::Error, "Write-method needs to be written for android");
        return true;
    }
    //////////////////////////////////////////

#endif

}