#include <Utility/FileHandler/FileHandlerAndroid.hpp>

#ifdef ANDROID

#include <android_native_app_glue.h>

namespace jej
{

    FileHandlerAndroid::FileHandlerAndroid(android_app* app):
        FileHandler(),
        m_app(new android_app(*(app)))
    {

    }

    FileHandlerAndroid::~FileHandlerAndroid()
    {
        if(m_app)
            delete m_app;
    }

    bool FileHandlerAndroid::read(const std::string& name, const unsigned int length)
    {

        AAsset* file = AAssetManager_open(m_app->activity->assetManager, name.c_str(), AASSET_MODE_BUFFER);

        if(!file)
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

        if(result < 0)
            Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", name);

        AAsset_close(file);

        return true;
    }


}

#endif
