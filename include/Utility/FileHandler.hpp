#ifndef JEJ_FILEHANDLER_HPP
#define JEJ_FILEHANDLER_HPP

#include <EntityComponentSys/Components/TextureComponent.hpp>

#ifdef _WIN32
#include <Utility/Windows.hpp>
#include <Windows.h>
#elif defined __ANDROID__
#include <android_native_app_glue.h>
#include <string>
#endif

#include <vector>

namespace jej
{
    class TextureComponent;
    struct TextureData;

    class FileHandler
    {
    public:

        //Constructor
#ifdef _WIN32
        FileHandler();
#elif defined __ANDROID__
        FileHandler(android_app* app);
#endif

        //Disabled copy-constructors
        NOCOPY(FileHandler);

        //Destructor
        ~FileHandler();

        //Name of the file to read with extension
        //Bytes to read, defaults to entire file
        bool Read(const std::string& p_name, const unsigned int p_length = 0u);

        //Read an image file, currently supports only .png files
        //p_data must have 'imagename' declared before this call
        bool ReadImage(TextureComponent::TextureData* p_data);

        //Writes m_fileContents to a file. Creates the file if it does not exist.
        //Name of the file to create
        bool Write(const std::string& name);

        //Reads a font file to memory
        //p_name: name of the file with extension
        //p_font: font to place to
        bool ReadFontFile(const std::string& p_name, TextureComponent::Font* p_font);

        //Returns reference to vector of data read on latest read call
        const std::vector<char>& GetReadDataRef() const;

        //Returns reference to vector of data read on latest read call
        std::vector<char>& GetReadDataRef();

        //Returns vector of data read on latest read call
        std::vector<char> GetReadData();

    private:

        //Name of the file with extension
        //Boolean for whether the file should be created if not present
        bool _accessFile(const std::string& p_name, const bool p_createFile);

        //Data that was read on latest read call.
        std::vector<char> m_fileContents;

    private:
#ifdef _WIN32

        //Handle to the file accessed by this instance
        HANDLE m_fileHandle;

#elif defined ANDROID

        //Android asset handler
        android_app* m_app;

#endif


    };
}

#endif