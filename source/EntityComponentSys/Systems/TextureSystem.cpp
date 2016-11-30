
#include <Core/BaseStructs.hpp>

#include <EntityComponentSys/Systems/TextureSystem.hpp>
#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>

namespace jej
{
    std::vector<std::shared_ptr<TextureComponent>> TextureSystem::m_components = {};

    TextureSystem::TextureSystem() :
        System()
    {

    }
    /////////////////////////////////


    TextureSystem::~TextureSystem()
    {

    }
    /////////////////////////////////

    TextureSystem& TextureSystem::GetInstance()
    {
        static TextureSystem system;
        return system;
    }
    /////////////////////////////////


    void TextureSystem::_bind(unsigned int p_unit)
    {

    }


    bool TextureSystem::_initialize(TextureData* p_data)
    {

        JEJ_ASSERT(!p_data->imageName.empty(), "No image name given!");

        const std::string imagePath = "Textures/" + p_data->imageName;

        FileHandler fileHandler;
        fileHandler.ReadImage(p_data);

        glGenTextures(1, &p_data->m_textureID);
        glBindTexture(GL_TEXTURE_2D, p_data->m_textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_data->wholeImageSize.x, p_data->wholeImageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_data->readImageData);

        if (glGetError() == GL_NO_ERROR)
            return true;
        else
            return false;
    }

    void TextureSystem::_drawFromSheet()
    {

    }


    void TextureSystem::_update(const float p_deltaTime)
    {

    }



}