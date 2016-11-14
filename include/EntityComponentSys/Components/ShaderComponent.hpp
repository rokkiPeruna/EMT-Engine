#ifndef JEJ_SHADER_COMPONENT_HPP
#define JEJ_SHADER_COMPONENT_HPP

#include <string>

#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>

namespace jej
{
	class ShaderComponent
	{
	public:

		enum class ShaderType
		{
			Fragment,
			Vertex
		};

		ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFilePath = "", const std::string& p_fragmentShaderPath = "");
		ShaderComponent::~ShaderComponent();


		void LinkShaders();
		void AddAttribute(const std::string& p_attributeName);
		void Use();
		void Unuse();

	private:

		void _compileShaders(const std::string& p_filePath, EGLint p_shaderId);
		bool _parseShader(const ShaderType type, const std::string& shader = std::string(""));

		std::string m_fragmentShader;
		std::string m_vertexShader;

		EGLint m_programId;
		EGLint m_vertexShaderId;
		EGLint m_fragmentShaderId;
		int m_numAttributes;



	};
}


#endif