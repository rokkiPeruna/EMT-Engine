#include <Core/Settings.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/FileHandler/FileHandlerWin32.hpp>

#include <EntityComponentSys/Systems/ShaderSystem.hpp>

#include <vector>
namespace jej
{
	ShaderSystem::ShaderSystem()
	{

	}
	/////////////////////////

	ShaderSystem::~ShaderSystem()
	{

	}
	/////////////////////////

	ShaderSystem& ShaderSystem::GetInstance()
	{
		static ShaderSystem system;
		return system;
	}
	/////////////////////////


	void ShaderSystem::_initialize(detail::ShaderData& p_sd)
	{

		if (!_parseShader(detail::ShaderType::vertex, p_sd.m_vertexShaderFileName))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse vertex shader ");
		}
		if (!_parseShader(detail::ShaderType::fragment, p_sd.m_fragmentShaderFileName))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to parse fragment shader ");
		}

		p_sd.m_program_ID = glCreateProgram();

		GLuint vertexShader = _loadShader((p_sd.m_vertexShaderFileName), GL_VERTEX_SHADER, detail::ShaderType::vertex);
		GLuint fragmentShader = _loadShader((p_sd.m_fragmentShaderFileName), GL_FRAGMENT_SHADER, detail::ShaderType::fragment);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		glAttachShader(p_sd.m_program_ID, vertexShader);
		glAttachShader(p_sd.m_program_ID, fragmentShader);

		_addAttribute(p_sd.m_program_ID, p_sd.m_numAttribute, "vPosition");
		_addAttribute(p_sd.m_program_ID, p_sd.m_numAttribute, "vTexCoord");

		glLinkProgram(p_sd.m_program_ID);

		GLint isLinked = 0;

		glGetProgramiv(p_sd.m_program_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to link program, shader creation failed ");

			glDeleteProgram(p_sd.m_program_ID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		glDetachShader(p_sd.m_program_ID, vertexShader);
		glDetachShader(p_sd.m_program_ID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}
	/////////////////////////
	void ShaderSystem::_addAttribute(GLuint& m_program_ID, int p_numAttribute, const std::string& p_attributeName)
	{
		glBindAttribLocation(m_program_ID, p_numAttribute++, p_attributeName.c_str());
	}
	/////////////////////////

	GLuint ShaderSystem::_loadShader(const std::string& p_shaderDataSource, const GLenum p_type, const detail::ShaderType p_shaderType)
	{
		GLuint shader;
		GLint success = 0;

		shader = glCreateShader(p_type);
		if (shader == 0)
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to create " + p_type);
		}

		const char* shaderData = _readFile(p_shaderType, p_shaderDataSource).c_str();

		glShaderSource(shader, 1, &shaderData, nullptr);

		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);

			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(shader);

			Messenger::Add(Messenger::MessageType::Error, "Compile shaders failed " + shader);
			return 0u;
		}

		return shader;
	}
	/////////////////////////

	bool ShaderSystem::_parseShader(const detail::ShaderType p_type, std::string& p_shaderName)
	{
		std::string path = "Shaders/";

		if (!p_shaderName.empty())
		{
			p_shaderName = path + p_shaderName;
			return true;
		}
		else
		{
			if (p_type == detail::ShaderType::vertex)
				p_shaderName = path + "FragmentShader.frag";
			else if (p_type == detail::ShaderType::fragment)
				p_shaderName = path + "VertexShader.vert";
			else
				return false;

			return true;
		}
	}
	/////////////////////////

	std::string ShaderSystem::_readFile(const detail::ShaderType p_type, std::string p_filePath)
	{
		FileHandlerWin32 handler;

		if (!handler.Read(p_filePath))
		{
			Messenger::Add(Messenger::MessageType::Error, "Failed to open shader file ", p_filePath);
			if (_parseShader(p_type, std::string("")))
			{
				if (!handler.Read(p_filePath))
				{
					Messenger::Add(Messenger::MessageType::Error, "Failed to open default shader file ", p_filePath);
					return "";
				}
			}
			else
			{
				Messenger::Add(Messenger::MessageType::Error, "Failed to parse default shader file ");
				return "";
			}
		}

		std::vector<char> v;
		std::string str(v.begin(), v.end());
		return str;

	}
	/////////////////////////

	void Use(const GLuint& p_program)
	{
		glUseProgram(p_program);
	}
	/////////////////////////

	void Unuse(const GLuint& p_program)
	{
		glUseProgram(p_program);
	}
	/////////////////////////

	void ShaderSystem::update(const float p_deltaTime)
	{
	}
	/////////////////////////

}