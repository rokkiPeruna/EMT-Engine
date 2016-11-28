#ifndef JEJ_TEXTURE_COMPONENT_HPP
#define JEJ_TEXTURE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <External/OpenGL_ES2/GLES2/gl2.h>

namespace jej
{
	class TextureComponent : public Component
	{

	public:

		TextureComponent::TextureComponent(Entity& p_entity , std::string& p_textureName);

		TextureComponent::~TextureComponent();

	private:

		// Texture name. Actual name of the PNG texture file
		std::string m_textureName;

		// Texture id 
		GLuint m_textureID;
	};

}
#endif