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

		// Check if user want's to include shaders
		bool _parseShader(const detail::ShaderType p_type, std::string& p_shaderName);
		
		// Read actual shader files (no matter where they are)
		std::string _readFile(const detail::ShaderType p_type ,std::string p_filePath);

		// Actually create shaders and bind them as one
		bool _createShader(GLuint& p_program ,const std::string& p_VertexFileSoucre, const std::string& FragmentFileSoucre);

		void Use();

		void Unuse();

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