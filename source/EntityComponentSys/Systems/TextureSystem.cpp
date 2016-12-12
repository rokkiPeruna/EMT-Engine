
#include <Core/BaseStructs.hpp>

#include <EntityComponentSys/Systems/TextureSystem.hpp>
#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <EntityComponentSys/Systems/ShapeSystem.hpp>

#include <Utility/Various.hpp>

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


    bool TextureSystem::_finalize()
    {
        for (auto& itr : m_components)
        {
            //Alias
            auto& name = itr->m_textureData.name;

            if (name.empty())
            {
                Messenger::Add(Messenger::MessageType::Warning, "No texture name given. Using default error texture.");
                name = settings::Settings::defaultErrorTextureName;
            }

            //png or ttf
            std::string type = "";
            const size_t dotPos = name.find_last_of(".");
            if (dotPos != std::string::npos)
                type = name.substr(dotPos + 1u);
            else
            {
                type = "png";
                name = settings::Settings::defaultErrorTextureName;
            }

            //Currentlty unsupported type
            if (type != "png" && type != "ttf")
            {
                JEJ_ASSERT(false, "Unsupported file type");
                Messenger::Add(Messenger::MessageType::Error, "Unsupported file type: " + type, "Using default texture instead.");
                name = settings::Settings::defaultErrorTextureName;
                type = "png";
            }

            //Image
            if (type == "png")
            {
                _bindImage(itr.get());
            }

            //Font
            else if (type == "ttf")
            {
                _fontStuff();
            }

        }
        return true;
    }
    //////////////////////////////////////////


    bool TextureSystem::_initialize()
    {
        return true;
    }
    //////////////////////////////////////////


    void TextureSystem::_update(const float p_deltaTime)
    {

    }
    //////////////////////////////////////////


    void TextureSystem::_bindImage(TextureComponent* p_component)
    {
        const std::string imagePath = "Textures/" + p_component->m_textureData.name;

        FileHandler fileHandler;
        fileHandler.ReadImage(&p_component->m_textureData);

        GLuint tempID;

        glGenTextures(1, &tempID);
        glBindTexture(GL_TEXTURE_2D, tempID);

       //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //Configure GL depending on target color format
        switch (p_component->m_textureData.offset)
        {

            //RGB
        case 3:
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                p_component->m_textureData.x,
                p_component->m_textureData.y,
                0, GL_RGB, GL_UNSIGNED_BYTE,
                p_component->m_textureData.data);

            break;
        }

        //RGBA
        default:
            Messenger::Add(Messenger::MessageType::Warning, "Unrecognized color format, using RGBA.");
        case 4:
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                p_component->m_textureData.x,
                p_component->m_textureData.y,
                0, GL_RGBA, GL_UNSIGNED_BYTE,
                p_component->m_textureData.data);

            break;
        }

        }

        if (glGetError() != GL_NO_ERROR)
        {
            Messenger::Add(Messenger::MessageType::Error, "Texture initialization failed.");
            JEJ_ASSERT(false, "Texture initialization failed.");
            //TextureID defaulted to -1 in struct ctor
            return;
        }

        //Connect correct Shape to this texture
        p_component->m_shapeData.textureID = static_cast<int>(tempID);
        ShapeSystem::GetInstance()._setTextureID(&p_component->m_shapeData);
    }
    //////////////////////////////////////////


    void TextureSystem::_drawFromSheet()
    {

    }
    //////////////////////////////////////////


    void TextureSystem::_fontStuff()
    {

    }
    //////////////////////////////////////////


}