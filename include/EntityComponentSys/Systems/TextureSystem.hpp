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
		
		// Short: initialize texture into standard spirte or sprite sheet.


		// Singleton constructor
		TextureSystem();


	public:

		// Delete copy constructor and operator =
		TextureSystem(const TextureSystem&) = delete;
		TextureSystem operator=(const TextureSystem&) = delete;

		// Destructor
		~TextureSystem();

		// Get the one and only instance of singleton 
		static TextureSystem& GetInstance();

	protected:

		// TODO: Bind texture
		void _bind(unsigned int p_unit);

		void _drawFromSheet();

		// Initialize texture
		bool _initialize(std::string& p_textureName, GLuint& p_textureID);
		
		// Basically useless but is required as part of system.hpp
		void _update(const float deltaTime);
	};
}

#endif