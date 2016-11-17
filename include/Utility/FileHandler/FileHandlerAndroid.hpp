#ifndef JEJ_FILEHANDLER_ANDROID_HPP
#define JEJ_FILEHANDLER_ANDROID_HPP

#if defined(ANDROID)

#include <Utility/FileHandler.hpp>

#include <android_native_app_glue.h>

namespace jej
{

    class FileHandlerAndroid : public FileHandler
    {
    public:

        //Constructor
        FileHandlerAndroid(android_app* app);

        //Disabled copy-constructors
        FileHandlerAndroid(const FileHandlerAndroid&) = delete;
        void operator=(const FileHandlerAndroid&) = delete;

        //Destructor
        ~FileHandlerAndroid();

        bool Read(const std::string& name, const unsigned int length = 0u) override;

        bool Write(const std::string& name) override;

    private:

        //Android asset handler
        android_app* m_app;

    };

}

#endif

#endif