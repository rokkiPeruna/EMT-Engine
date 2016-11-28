#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

#include <Utility/Messenger.hpp>

namespace jej
{
	TextureComponent::TextureComponent(Entity& p_entity, std::string& p_textureName) :
		Component(p_entity),
		m_textureName(p_textureName),
		m_textureID(0u)
	{
		if (!TextureSystem::GetInstance()._initialize(p_textureName, m_textureID))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to create texture ");
		}
	}

	TextureComponent::~TextureComponent()
	{

	}


}