
//All Android-specific definitions in this file

#ifdef __ANDROID__

#include <Core/AndroidAppState.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>


namespace jej
{

    FileHandler::FileHandler() :
        m_fileContents(),
        m_app(nullptr)
    {
        m_app = new android_app(*(AndroidAppState::m_AppState));
    }
    //////////////////////////////////////////


    FileHandler::~FileHandler()
    {
        if (m_app)
        {
            delete m_app;
            m_app = nullptr;
        }

    }
    //////////////////////////////////////////


    bool FileHandler::Read(const std::string& name, const unsigned int length)
    {

        AAsset* file = AAssetManager_open(m_app->activity->assetManager, name.c_str(), AASSET_MODE_BUFFER);

        if (!file)
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

        if (result < 0)
            Messenger::Add(Messenger::MessageType::Error, "Failed to read file: ", name);

        AAsset_close(file);

        return true;
    }
    //////////////////////////////////////////

	bool FileHandler::ReadFontFile(const std::string& p_name, TextureComponent::Font* p_font)
	{
		//TODO: Add Android stuff
		return false;
	}

	bool FileHandler::ReadImage(TextureComponent::TextureData* p_data)
	{

       //const std::string imagePath = "Textures/" + p_data->name;
        const std::string imagePath = p_data->name;


        AAsset* file = AAssetManager_open(m_app->activity->assetManager, imagePath.c_str(), AASSET_MODE_BUFFER);

        unsigned char* buffer;

        p_data->size = AAsset_getLength(file);

        AAsset_read(file, buffer, p_data->size);
        if (!file)
        {
            Messenger::Add(Messenger::MessageType::Error, "Texture could not be read");
            return false;
        }
        //const char* tmpData = (char*)AAsset_getBuffer(file);
        //Used for copying data

        AAsset_close(file);

        //Load image
        p_data->data = stbi_load_from_memory(
                buffer,
                p_data->size,
            &p_data->x,
            &p_data->y,
            &p_data->offset,
            0);


        if (!p_data->data)
            return false;

        return true;
	}
	//////////////////////////////////////////

    bool FileHandler::Write(const std::string& name)
    {
        Messenger::Add(Messenger::MessageType::Error, "Write-method needs to be written for android");
        return true;
    }
    //////////////////////////////////////////


    bool FileHandler::_accessFile(const std::string& p_name, const bool p_createFile)
    {
        //Not needed in Android
        return false;
    }
	//////////////////////////////////////////

	void FileHandler::_releaseHandle()
	{
		//Not needed Android
	}

	

}

#endif
