
#include <Core/BaseStructs.hpp>

#include <EntityComponentSys/Systems/TextureSystem.hpp>
#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>

//temp
#include <Core/Scene.hpp>

namespace jej
{
    std::vector<std::shared_ptr<TextureComponent>> TextureSystem::m_components = {};

    TextureSystem::TextureSystem() :
        System()
    {

    }
    //////////////////////////////////////////


    TextureSystem::~TextureSystem()
    {

    }
    //////////////////////////////////////////


    TextureSystem& TextureSystem::GetInstance()
    {
        static TextureSystem system;
        return system;
    }
    //////////////////////////////////////////


    void TextureSystem::_bind(unsigned int p_unit)
    {

    }
    //////////////////////////////////////////


    void TextureSystem::_drawFromSheet()
    {

    }
    //////////////////////////////////////////


    void TextureSystem::_update(const float p_deltaTime)
    {

    }
    //////////////////////////////////////////


    bool TextureSystem::_finalize()
    {
        for (auto& itr : m_components)
        {
            JEJ_ASSERT(!itr->m_texData.name.empty(), "No image name given!");

            const std::string imagePath = "Textures/" + itr->m_texData.name;

            FileHandler fileHandler;
            fileHandler.ReadImage(&itr->m_texData);

            GLuint tempID;


            glGenTextures(1, &tempID);
            glBindTexture(GL_TEXTURE_2D, tempID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned char* data = new unsigned char[itr->m_texData.data.size()];
            for (unsigned int i = 0u; i < itr->m_texData.data.size(); ++i)
                data[i] = itr->m_texData.data[i];

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                itr->m_texData.x,
                itr->m_texData.y,
                0, GL_RGBA, GL_UNSIGNED_BYTE,
                data);

            delete[]data;

            if (glGetError() != GL_NO_ERROR)
            {
                Messenger::Add(Messenger::MessageType::Error, "Texture initialization failed by OpenGL.");
                itr->m_textureID = -1;
                JEJ_ASSERT(false, "Texture initialization failed.");
                return false;
            }

            itr->m_textureID = static_cast<int>(tempID);




        }
        return true;
    }
    //////////////////////////////////////////


    bool TextureSystem::_initialize()
    {





        //JEJ_ASSERT(!p_data->imageName.empty(), "No image name given!");


        //const std::string imagePath = "Textures/" + p_data->imageName;


        //unsigned int width, height, numComponents;



        //	glGenTextures(1, &p_data->m_textureID);
        //
        //    glBindTexture(GL_TEXTURE_2D, p_data->m_textureID);
        //
        //
        //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //
        //	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //
        //	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_data->wholeImageSize.x, p_data->wholeImageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_data->readImageData.data());


        return true;
    }
    //////////////////////////////////////////


}