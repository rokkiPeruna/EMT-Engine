#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

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
            JEJ_ASSERT(false, "Texture initialization failed!");
	}

    TextureComponent::~TextureComponent()
    {

	}

    const TextureData TextureComponent::GetTextureData() const
    {
        return m_textureData;
    }

    TextureData TextureComponent::GetTextureData()
    {
        return m_textureData;
    }

}