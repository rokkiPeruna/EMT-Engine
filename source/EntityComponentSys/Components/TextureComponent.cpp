#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <EntityComponentSys/Systems/TextureSystem.hpp>

namespace jej
{
	TextureComponent::TextureComponent(Entity& p_entity, const std::string& p_textureName) :
		Component(p_entity),
		m_textureName(p_textureName)
	{
		TextureSystem::GetInstance()._initialize(p_textureName);
	}

	TextureComponent::~TextureComponent()
	{

	}


}