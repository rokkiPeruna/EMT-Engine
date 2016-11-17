#include <Core/Settings.hpp>
#include <Utility/FileHandler/FileHandlerWin32.hpp>
#include <Utility/Windows/Windows.hpp>

namespace jej
{

    FileHandlerWin32::FileHandlerWin32() :
        FileHandler(),
        m_fileHandle(nullptr)
    {

    }
    /////////////////////////////////


    FileHandlerWin32::~FileHandlerWin32()
    {
        if (m_fileHandle)
            CloseHandle(m_fileHandle);
    }
    /////////////////////////////////


    bool FileHandlerWin32::Read(const std::string& name, const unsigned int length)
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

        //Add string terminator
        m_fileContents.emplace_back('\0');

        return true;
    }
    /////////////////////////////////


    bool FileHandlerWin32::Write(const std::string& name)
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
    /////////////////////////////////


    bool FileHandlerWin32::accessFile(const std::string& name, const bool createFile)
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
    /////////////////////////////////

}