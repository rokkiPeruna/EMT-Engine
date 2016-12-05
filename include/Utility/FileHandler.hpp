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

    //All Declarations in this file
    class FileHandler
    {

    public:

        //Constructor
        FileHandler();

        //Disabled copy-constructors
        NOCOPY(FileHandler);

        //Destructor
        ~FileHandler();

        //Name of the file to read with extension
        //Bytes to read, defaults to entire file
        bool Read(const std::string& p_name, const unsigned int p_length = 0u);

        //Reads a font file to memory
        //p_name: name of the file with extension
        //p_font: font to place to
        bool ReadFontFile(const std::string& p_name, TextureComponent::Font* p_font);

        //Read an image file, currently supports only .png files
        //p_data must have 'imagename' declared before this call
        bool ReadImage(TextureComponent* p_component);

        //Sets 'displayImage' in p_data to an image pointed to by p_index, calculated from size in p_data, from p_wholeImageData
        //p_data should therefore be constructed with p_wholeImageData
        bool ReadSingleImage(TextureComponent::TextureData* p_data, const unsigned char* p_wholeImageData, const unsigned int p_index); 

        //Writes m_fileContents to a file. Creates the file if it does not exist.
        //Name of the file to create
        bool Write(const std::string& name);

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

        void _releaseHandle();

        //Data that was read on latest read call.
        std::vector<char> m_fileContents;


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