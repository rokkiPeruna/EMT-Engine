#ifndef JEJ_FILEHANDLER_WIN32_HPP
#define JEJ_FILEHANDLER_WIN32_HPP

#ifdef _WIN32

#include <Utility/FileHandler/FileHandler.hpp>

namespace jej
{

    class FileHandlerWin32 : public FileHandler
    {

    public:

        //Constructor
        FileHandlerWin32();

        //Disabled copy-constructors
        FileHandlerWin32(const FileHandlerWin32&) = delete;
        void operator=(const FileHandlerWin32&) = delete;

        //Destructor
        ~FileHandlerWin32();

        bool Read(const std::string& name, const unsigned int length = 0u) override;

        bool Write(const std::string& name) override;

    private:

        //Handle to the file accessed by this instance
        HANDLE m_fileHandle;

        //Name of the file with extension
        //Boolean for whether the file should be created if not present
        bool accessFile(const std::string& name, const bool createFile);

    };


}

#endif

#endif