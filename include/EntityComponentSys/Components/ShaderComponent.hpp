#ifndef JEJ_SHADER_COMPONENT_HPP
#define JEJ_SHADER_COMPONENT_HPP

#include <string>

#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>

#include <EntityComponentSys/Components/Component.hpp>

namespace jej
{
	class ShaderComponent : public Component
	{
	public:

		enum class ShaderType
		{
			Fragment,
			Vertex
		};
		// constructor for shader
		ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFilePath = "", const std::string& p_fragmentShaderPath = "");
		ShaderComponent::~ShaderComponent();

		// Set shader on use
		void Bind();

	private:
		// Create shader
		static GLuint _createShader(const std::string& p_fileSource, GLenum p_shaderType);

		// Set default shader in use, or users own shader
		bool _parseShader(const ShaderType type, const std::string& shader = nullptr);

		// Read shaders from shader files (TODO: possibly change from ifstream to our own)
		std::string _readFile(const char* p_filePath);

		// Filepaths for shaders
		std::string m_fragmentShaderFilePath;
		std::string m_vertexShaderFilePath;

		// Actual shader (vertex and fragment combined
		GLuint m_program_ID;
		
		//Fragment and Vertex shaders
		GLuint m_vertexShader_ID;
		GLuint m_fragmentShader_ID;

	};
}


#endif