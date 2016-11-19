#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <Utility/Messenger.hpp>
#include <Core/Settings.hpp>

#include <EntityComponentSys/Systems/ShaderSystem.hpp>

// TODO:: remove if we use our own read system
#include <fstream>

namespace jej
{
	ShaderComponent::ShaderComponent(const std::string& p_vertexShaderFileName, const std::string& p_fragmentShaderFileName) :
	Component()
	{
		m_componentType = ComponentType::Shader;
		
		m_shaderData.m_vertexShaderFileName = p_vertexShaderFileName;
		m_shaderData.m_fragmentShaderFileName = p_fragmentShaderFileName;

		ShaderSystem::GetInstance()._initialize(m_shaderData);

	}

	ShaderComponent::~ShaderComponent()
	{

	}

}