#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <Utility/Messenger.hpp>
#include <Core/Settings.hpp>


// TODO:: remove if we use our own read system
#include <fstream>

namespace jej
{
	ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFilePath, const std::string& p_fragmentShaderPath) :
	Component(),
	m_vertexShaderFilePath(p_vertexShaderFilePath),
	m_fragmentShaderFilePath(p_fragmentShaderPath),
	m_program_ID(0),
	m_vertexShader_ID(0),
	m_fragmentShader_ID(0)
	{
		m_componentType = ComponentType::Shader;

		m_program_ID = glCreateProgram();

		// Check if there is user implemented shader, otherwise use default shaders
		if (!_parseShader(ShaderType::Vertex, m_vertexShaderFilePath))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse vertex shader");
		}
		if (!_parseShader(ShaderType::Fragment, m_fragmentShaderFilePath))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse fragment shader");
		}

		_createShader(m_vertexShaderFilePath, GL_VERTEX_SHADER);
		_createShader(m_fragmentShaderFilePath, GL_FRAGMENT_SHADER);

		glAttachShader(m_program_ID, m_vertexShader_ID);
		glAttachShader(m_program_ID, m_fragmentShader_ID);

		glBindAttribLocation(m_program_ID, 0, "vPosition");
		glBindAttribLocation(m_program_ID, 1, "vTexCoord");

		glLinkProgram(m_program_ID);
		glValidateProgram(m_program_ID);

	}

	ShaderComponent::~ShaderComponent()
	{
		glDetachShader(m_program_ID, m_vertexShader_ID);
		glDetachShader(m_program_ID, m_fragmentShader_ID);

		glDeleteShader(m_vertexShader_ID);
		glDeleteShader(m_fragmentShader_ID);

		glDeleteProgram(m_program_ID);

	}


	void ShaderComponent::Bind()
	{
		glUseProgram(m_program_ID);
	}

	GLuint ShaderComponent::_createShader(const std::string& p_fileSource, GLenum p_shaderType)
	{
		GLuint shader = glCreateShader(p_shaderType);

		if (shader == 0)
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to create " + p_shaderType);
		}

		const GLchar* p[1];
		GLint pL[1];

		p[0] = p_fileSource.c_str();
		pL[0] = p_fileSource.length();

		glShaderSource(shader, 1, p, pL);
		glCompileShader(shader);



		return shader;
	}

	bool ShaderComponent::_parseShader(const ShaderType type, const std::string& shader)
	{
		if (!shader.empty())
		{
			if (type == ShaderType::Fragment)
			{
				m_fragmentShaderFilePath = shader;
				return true;
			}
			else if (type == ShaderType::Vertex)
			{
				m_vertexShaderFilePath = shader;
				return true;
			}
		}

		std::string ShaderName = settings::rootPath + "Resources/Shaders";

		if (type == ShaderType::Fragment)
			ShaderName += "FragmentShader.frag";
		else if (type == ShaderType::Vertex)
			ShaderName += "VertexShader.vert";
		else
			return false;
		
		return true;
	}


	// TODO: Replace with our own reading system if required
	std::string ShaderComponent::_readFile(const char* p_filePath)
	{
		std::string fileContent = "";
		std::ifstream readFile(p_filePath, std::ios::in);

		if (!readFile.is_open())
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to open file ");
			return "";
		}

		std::string line = "";
		while (!readFile.eof())
		{
			std::getline(readFile, line);
			fileContent.append(line + "\n");
		}

		readFile.close();
		return fileContent;
	}



}