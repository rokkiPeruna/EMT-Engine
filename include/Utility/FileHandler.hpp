#ifndef JEJ_FILEHANDLER_HPP
#define JEJ_FILEHANDLER_HPP

#include <Utility/Messenger.hpp>

#ifdef _WIN32

#include <Utility/Windows.hpp>
#include <Windows.h>

#elif defined ANDROID

#include <android_native_app_glue.h>

#endif

#include <vector>

namespace jej
{
	class FileHandler
	{
	public:

		//Constructor
		FileHandler();

		//Disabled copy-constructors
		FileHandler(const FileHandler&) = delete;
		void operator=(const FileHandler&) = delete;

		//Destructor
		~FileHandler();

        //Name of the file to read with extension
        //Bytes to read, defaults to entire file
        bool Read(const std::string& name, const unsigned int length = 0u);

        //Writes m_fileContents to a file. Creates the file if it does not exist.
        //Name of the file to create
        bool Write(const std::string& name);

		std::vector<char> m_fileContents;

    private:

#ifdef _WIN32

        //Handle to the file accessed by this instance
        HANDLE m_fileHandle;

        //Name of the file with extension
        //Boolean for whether the file should be created if not present
        bool accessFile(const std::string& name, const bool createFile);

#elif defined ANDROID

        //Android asset handler
        android_app* m_app;

#endif


	};
}

#endif