#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Texture/Shape.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>

namespace jej
{


    TextureComponent::TextureComponent(Entity* p_entity, const JEJ_COUNT p_shapeID):
        Component(p_entity),
        m_fontData(),
        m_texData(),
        m_shapeID(p_shapeID)
    {

    }

    TextureComponent::TextureComponent(Entity* p_entity, Shape* p_shape):
        Component(p_entity),
        m_fontData(),
        m_texData(),
        m_shapeID(p_shape->GetID())
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

    bool TextureComponent::AddImage(const std::string& p_name, const unsigned short int p_imageCount)
    {
        m_texData.name = p_name;
        return true;
     //   m_textureData.imageCount = p_imageCount;
     //   m_textureData.imageName = p_name;
     //   FileHandler handler;
     //   if (handler.ReadImage(this))
     //   {
     //       m_textureData.displayImage = new unsigned char[m_textureData.imageDataSize];
     //       std::memcpy(m_textureData.displayImage, m_completeImageData, m_textureData.imageDataSize);
     //
     //       //Both pointers contain same-size arrays after this with same data
     //
     //       return true;
     //   }
     //   return false;
    }
    //////////////////////////////////////////


    bool TextureComponent::UseImage(const unsigned int p_imageIndex)
    {
        FileHandler handler;
        return false;
        //return handler.ReadSingleImage(&m_textureData, m_completeImageData, p_imageIndex);
    }
    //////////////////////////////////////////


    bool TextureComponent::AddFont(const std::string& p_name)
    {
        FileHandler handler;
        m_fontData.fontInfo.data = (unsigned char*)std::string(settings::rootPath + "Resources/" + p_name).c_str();
        return handler.ReadFontFile(p_name, &m_fontData);
    }
    //////////////////////////////////////////


}