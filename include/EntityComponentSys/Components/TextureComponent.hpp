#ifndef JEJ_TEXTURE_COMPONENT_HPP
#define JEJ_TEXTURE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>

namespace jej
{
	namespace detail
	{
		struct TextureData
		{
			unsigned int width = 0u;
			unsigned int height = 0u;
			std::string data = "";

		};
	}
	class TextureComponent : public Component
	{

	public:

		TextureComponent::TextureComponent(Entity& p_entity ,const std::string& p_textureName);

		TextureComponent::~TextureComponent();

	private:

		std::string m_textureName;

	};

}
#endif