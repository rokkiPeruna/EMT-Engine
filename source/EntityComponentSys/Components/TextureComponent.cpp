#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>

namespace jej
{

	TextureComponent::TextureComponent(Entity* entity, const TextureData& p_data) :
        Component(entity),
		m_imageData(),
		m_textureData(p_data)
    {
        m_componentType = ComponentType::Texture;

		JEJ_ASSERT(!m_textureData.imageName.empty(), "No texture name given");


        FileHandler handler;
        if (handler.ReadImage(m_textureData.imageName)
        {
            m_data.assign(handler.m_fileContents.begin(), handler.m_fileContents.end());
        }

    }

    TextureComponent::~TextureComponent()
    {

    }

    std::vector<char> TextureComponent::_getImage(const unsigned int p_index)
    {
        std::vector<char> imageData = {};

        if (m_data.empty())
        {
            Messenger::Add(Messenger::MessageType::Error, "No image loaded.");
            return imageData;
        }

        

        if (p_index >= m_count)
        {
            Messenger::Add(Messenger::MessageType::Error, "Index too large.");
            return imageData;
        }

        const unsigned int imageBytes = m_data.size() / m_count;
        const unsigned int imageStart = p_index * imageBytes;

        //Copies data from m_data 
        //beginning from imageStart
        //ending in final index or imageStart + imageBytes
        imageData.assign(m_data[imageStart], imageStart + imageBytes >= m_data.size() ? m_data[m_data.size() - 1u] : m_data[imageStart + imageBytes]);
        return imageData;
    }

}