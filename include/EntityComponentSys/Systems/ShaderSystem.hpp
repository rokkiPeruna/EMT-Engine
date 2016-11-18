#ifndef JEJ_SHADER_SYSTEM_HPP
#define JEJ_SHADER_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>

#include <memory>



namespace jej
{

	class ShaderSystem : public System
	{
		friend class EngineObject;
		friend class Entity;
		friend class ShaderComponent;

	private:



		ShaderSystem();

		static std::vector<std::shared_ptr<ShaderComponent>> m_components;

		// Initialize runs through other functions
		void _initialize(detail::ShaderData& p_sd);

		// Adds attribute to structs num attibute.
		void _addAttribute(GLuint& p_program, int p_numAttribute ,const std::string& p_attributeName);

		// Load shaders from file and compiles them as usable shader.
		GLuint _loadShader(const std::string& p_shaderDataSource, const GLenum p_type, const detail::ShaderType p_shaderType);

		// Check if user want's to include shaders
		bool _parseShader(const detail::ShaderType p_type, std::string& p_shaderName);
		
		// Read actual shader files (no matter where they are)
		std::string _readFile(const detail::ShaderType p_type ,std::string p_filePath);

		// Enable shader
		void Use(const GLuint& p_program);

		// Disable shader
		void Unuse(const GLuint& p_program);

	public:


		ShaderSystem(const ShaderSystem&) = delete;
		ShaderSystem operator=(const ShaderSystem&) = delete;

		~ShaderSystem();

		static ShaderSystem& GetInstance();


	protected:

		void update(const float p_deltaTime);


	};

}


#endif