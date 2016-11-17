#ifndef JEJ_FILEHANDLER_HPP
#define JEJ_FILEHANDLER_HPP

#include <Utility/Messenger.hpp>

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
		virtual bool Read(const std::string& name, const unsigned int length = 0u) = 0;

        //Writes m_fileContents to a file. Creates the file if it does not exist.
        //Name of the file to create
        virtual bool Write(const std::string& name) = 0;

		std::vector<char> m_fileContents;

	};
}

#endif