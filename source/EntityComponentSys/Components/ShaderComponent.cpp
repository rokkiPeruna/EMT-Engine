#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <Utility/Messenger.hpp>
#include <Core/Settings.hpp>


// TODO:: remove if we use our own read system
#include <fstream>

namespace jej
{
	ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFilePath, const std::string& p_fragmentShaderPath) :
		m_vertexShader(p_vertexShaderFilePath),
		m_fragmentShader(p_fragmentShaderPath),
		m_programId(0),
		m_vertexShaderId(0),
		m_fragmentShaderId(0),
		m_numAttributes(0)
	{
		m_programId = glCreateProgram();

		// Check if there is user implemented shader, otherwise use default shaders
		if (!_parseShader(ShaderType::Vertex, m_vertexShader));
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse vertex shader");
		}

		if (!_parseShader(ShaderType::Fragment, m_fragmentShader));
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse fragment shader");
		}

		m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShaderId == 0)
			Messenger::Add(Messenger::MessageType::Error, "Failed to create vertex shader! ");
		
		m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShaderId == 0)
			Messenger::Add(Messenger::MessageType::Error, "Failed to create fragment shader! ");


		_compileShaders(m_vertexShader, m_vertexShaderId);
		_compileShaders(m_fragmentShader, m_fragmentShaderId);

	}

	ShaderComponent::~ShaderComponent()
	{


	}

	void _compileShaders(const std::string& p_filePath, EGLint p_shaderId)
	{
		// Add our own reading system

		std::ifstream shaderFile(p_filePath);
		if (shaderFile.fail)
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to open file " + p_filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line))
		{
			fileContents += line + "\n";
		}
		shaderFile.close();


	}


	bool ShaderComponent::_parseShader(const ShaderType type, const std::string& shader)
	{
		if (!shader.empty())
		{
			if (type == ShaderType::Fragment)
			{
				m_fragmentShader = shader;
				return true;
			}
			else if (type == ShaderType::Vertex)
			{
				m_vertexShader = shader;
				return true;
			}

		}

		std::string ShaderName = settings::rootPath + "Resources/Shaders";

		if (shader.empty())
		{
			if (type == ShaderType::Fragment)
			{
				ShaderName += "FragmentShader.frag";
			}
			else if (type == ShaderType::Vertex)
			{
				ShaderName += "VertexShader.vert";
			}
			else
			{
				return false;
			}
		}
	}



}