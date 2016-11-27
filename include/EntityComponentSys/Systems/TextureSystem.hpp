#ifndef JEJ_TEXTURE_SYSTEM_HPP
#define JEJ_TEXTURE_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <Utility/FileHandler.hpp>


#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>


namespace jej
{
	class TextureSystem : public System 
	{
		friend class TextureComponent;


	private:
		
		TextureSystem();


	public:

		TextureSystem(const TextureSystem&) = delete;
		TextureSystem operator=(const TextureSystem&) = delete;

		~TextureSystem();

		static TextureSystem& GetInstance();

	protected:

		void _bind(unsigned int p_unit);
		void _initialize(const std::string& p_textureName);
		void _update(const float deltaTime);
	
	};
}

#endif