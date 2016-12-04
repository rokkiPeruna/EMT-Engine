#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>

#include <Utility/FileHandler.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Assert.hpp>

namespace jej
{

	TextureComponent::TextureComponent(Entity* p_entity, const std::string& p_name) :
        Component(p_entity),
		m_textureData()
	{
        m_componentType = ComponentType::Texture;

        m_textureData.imageName = p_name;
        
        if (!TextureSystem::GetInstance()._initialize(&m_textureData))
        {
            JEJ_ASSERT(false, "Texture initialization failed!");
        }

	}

    TextureComponent::~TextureComponent()
    {

	}

   // std::vector<char> TextureComponent::_getImage(const unsigned int p_index)
   // {
   //     std::vector<char> imageData = {};
   //
   //     if (m_data.empty())
   //     {
   //         Messenger::Add(Messenger::MessageType::Error, "No image loaded.");
   //         return imageData;
   //     }
   //
   //     
   //
   //     if (p_index >= m_count)
   //     {
   //         Messenger::Add(Messenger::MessageType::Error, "Index too large.");
   //         return imageData;
   //     }
   //
   //     const unsigned int imageBytes = m_data.size() / m_count;
   //     const unsigned int imageStart = p_index * imageBytes;
   //
   //     //Copies data from m_data 
   //     //beginning from imageStart
   //     //ending in final index or imageStart + imageBytes
   //     imageData.assign(m_data[imageStart], imageStart + imageBytes >= m_data.size() ? m_data[m_data.size() - 1u] : m_data[imageStart + imageBytes]);
   //     return imageData;
   // }

}