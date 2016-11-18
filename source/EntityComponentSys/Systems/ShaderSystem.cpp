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

	ShaderSystem::~ShaderSystem()
	{


	}

	ShaderSystem& ShaderSystem::GetInstance()
	{
		static ShaderSystem system;
		return system;
	}

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

		_createShader(p_sd.m_program_ID, p_sd.m_vertexShaderFileName, p_sd.m_fragmentShaderFileName);

	}

	bool ShaderSystem::_createShader(GLuint& p_program, const std::string& p_VertexFileSoucre, const std::string& FragmentFileSoucre)
	{
		GLuint vertexShader = 0u;
		GLuint fragmentShader = 0u;

		//GL set shader


	}

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

	void Use()
	{
		//	glUseProgram(m_program_ID);
	}
	void Unuse()
	{
		//	glUseProgram(m_program_ID);
	}

	void ShaderSystem::update(const float p_deltaTime)
	{

	}


}