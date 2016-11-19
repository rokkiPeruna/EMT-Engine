#include <EntityComponentSys/Components/SpriteComponent.hpp>
#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>

namespace jej
{

    SpriteComponent::SpriteComponent(const std::string& p_name, const Vector2f& p_sizeOne, const unsigned int p_count, const unsigned int p_startImage) :
        Component(),
        m_data(),
        m_sizeOne(p_sizeOne),
        m_count(p_count)
    {
        m_componentType = ComponentType::Sprite;


        FileHandler handler;
        if (handler.Read(p_name))
        {
            m_data.assign(handler.m_fileContents.begin(), handler.m_fileContents.end());
        }

    }

    SpriteComponent::~SpriteComponent()
    {

    }

    std::vector<char> SpriteComponent::_getImage(const unsigned int p_index)
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