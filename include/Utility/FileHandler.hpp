#ifndef JEJ_FILEHANDLER_HPP
#define JEJ_FILEHANDLER_HPP

#ifdef _WIN32
#include <Utility/Windows.hpp>
#include <Windows.h>
#elif defined ANDROID
#include <android_native_app_glue.h>
#endif


#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include <External/STB/stb_truetype.h>

#include <vector>

namespace jej
{
    class TextureComponent;
    struct TextureData;

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

        //Read an image file, currently supports only .png files
        //p_data must have 'imagename' declared before this call
		bool ReadImage(TextureData* p_data);

        //Writes m_fileContents to a file. Creates the file if it does not exist.
        //Name of the file to create
        bool Write(const std::string& p_name);

        //Reads a font file to memory
        //p_name: name of the file with extension
        bool ReadFontFile(const std::string& p_name);

        //Returns font info
        const stbtt_fontinfo GetFontInfo() const;

        //Returns font info
        stbtt_fontinfo GetFontInfo();

        //Returns vector of data read on latest read call
        const std::vector<char> GetReadData() const;

        //Returns vector of data read on latest read call
        std::vector<char> GetReadData();


    private:

        //Data that was read on latest read call.
        std::vector<char> m_fileContents;

        //Data from a font file
        stbtt_fontinfo m_fontInfo;

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