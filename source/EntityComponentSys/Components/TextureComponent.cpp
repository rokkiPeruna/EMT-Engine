#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Texture/Shape.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

#include <EntityComponentSys/Entity/Entity.hpp>

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>

namespace jej
{


    TextureComponent::TextureComponent(Entity* p_entity, const JEJ_COUNT p_shapeID) :
        Component(p_entity),
        m_fontData(),
        m_textureData(),
        m_shapeData(p_entity->GetID(), p_shapeID, -1)
    {

    }

    TextureComponent::TextureComponent(Entity* p_entity, Shape* p_shape) :
        Component(p_entity),
        m_fontData(),
        m_textureData(),
        m_shapeData(p_entity->GetID(), p_shape->GetID(), -1)
    {

    }


    //  TextureComponent::TextureComponent(Entity* p_entity) :
    //      Component(p_entity),
    //      m_fontData(),
    //     m_texData()
    //     // m_textureData(),
    //      //m_completeImageData(nullptr)
    //  {
    //      m_componentType = ComponentType::Texture;
    //
    //  }
    //////////////////////////////////////////


    TextureComponent::~TextureComponent()
    {
        //Free texture if present (also called in texdata dtor)
        //   if (m_textureData.displayImage)
        //   {
        //       delete[] m_textureData.displayImage;
        //       m_textureData.displayImage = nullptr;
        //   }
        //
        //Free fontdata if present (also called in texcomp dtor)
        if (m_fontData.fontData)
        {
            stbi_image_free(m_fontData.fontData);
            m_fontData.fontData = nullptr;
        }
        //
        //   //Free whole image if present
        //   if (m_completeImageData)
        //   {
        //       stbi_image_free(m_completeImageData);
        //       m_completeImageData = nullptr;
        //   }

    }
    //////////////////////////////////////////


    //  const TextureComponent::TextureData& TextureComponent::GetTextureDataRef() const
    //  {
    //      return m_textureData;
    //  }
    //
    //  TextureComponent::TextureData& TextureComponent::GetTextureDataRef()
    //  {
    //      return m_textureData;
    //  }

    bool TextureComponent::AddImage(const std::string& p_name, const Vector2i p_imageCount)
    {
        m_textureData.name = p_name;
        m_textureData.imagesInTexture = p_imageCount;
        return true;
    }
    //////////////////////////////////////////


    bool TextureComponent::UseImage(const int p_imageIndex)
    {
        const int imageCount = m_textureData.imagesInTexture.x * m_textureData.imagesInTexture.y;
        
        if (imageCount <= p_imageIndex)
        {
            JEJ_ASSERT(false, "Invalid index");
            Messenger::Add(Messenger::MessageType::Error, "Tried to access " + std::to_string(p_imageIndex) + " th image from a file with " + std::to_string(imageCount) + " images");
            return false;
        }

        m_textureData.usingImage = p_imageIndex;
        m_textureData.hasChanged = true;
        return true;
    }
    //////////////////////////////////////////


    bool TextureComponent::AddFont(const std::string& p_name)
    {
        FileHandler handler;
        m_fontData.fontInfo.data = (unsigned char*)std::string(settings::Settings::rootPath + "Resources/" + p_name).c_str();
        return handler.ReadFontFile(p_name, &m_fontData);
    }
    //////////////////////////////////////////


}