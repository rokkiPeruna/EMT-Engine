#ifndef JEJ_SHADER_COMPONENT_HPP
#define JEJ_SHADER_COMPONENT_HPP

#include <string>

//#include <External\OpenGL_ES2\EGL\egl.h>

#include <EntityComponentSys/Components/Component.hpp>

namespace jej
{
	namespace detail
	{
		enum class ShaderType
		{
			vertex,
			fragment
		};

		struct ShaderData
		{
			// Actual shader (vertex and fragment combined
			unsigned int m_program_ID;

			ShaderType m_type;

			// Filepaths for shaders
			std::string m_vertexShaderFileName;
			std::string m_fragmentShaderFileName;

			int amountOfAttributes;

			ShaderData(){}
		};
	}
	class ShaderComponent : public Component
	{
	public:


		// constructor for shader
		ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFileName = "", const std::string& p_fragmentShaderFileName = "");
		ShaderComponent::~ShaderComponent();

	private:
		
		detail::ShaderData m_shaderData;



	};

}


#endif