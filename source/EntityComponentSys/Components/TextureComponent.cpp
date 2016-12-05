#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>

namespace jej
{

    TextureComponent::TextureComponent(Entity* p_entity, const std::string& p_name, const unsigned short int p_imageCount, const std::vector<unsigned char>& p_selectedImages) :
        Component(p_entity),
        m_textureData(),
        m_completeImageData(nullptr)
    {
        m_componentType = ComponentType::Texture;

        m_textureData.imageName = p_name;
        m_textureData.imageCount = p_imageCount;
        m_textureData.selectedImages = p_selectedImages;
    }

    TextureComponent::~TextureComponent()
    {
        //Free texture if present (also called in texdata dtor)
        if (m_textureData.displayImage)
        {
            stbi_image_free(m_textureData.displayImage);
            m_textureData.displayImage = nullptr;
        }

        //Free fontdata if present (also called in texcomp dtor)
        if (m_fontData.fontData)
        {
            stbi_image_free(m_fontData.fontData);
            m_fontData.fontData = nullptr;
        }

        //Free whole image
        if (m_completeImageData)
        {
            stbi_image_free(m_completeImageData);
            m_completeImageData = nullptr;
        }

    }

    const TextureComponent::TextureData& TextureComponent::GetTextureData() const
    {
        return m_textureData;
    }

    TextureComponent::TextureData& TextureComponent::GetTextureData()
    {
        return m_textureData;
    }

}