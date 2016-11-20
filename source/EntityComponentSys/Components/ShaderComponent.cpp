#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <Utility/Messenger.hpp>
#include <Core/Settings.hpp>

#include <EntityComponentSys/Systems/ShaderSystem.hpp>

// TODO:: remove if we use our own read system
#include <fstream>

namespace jej
{
    ShaderComponent::ShaderComponent(Entity& entity, const std::string& p_fragmentShaderFileName, const std::string& p_vertexShaderFileName) :
        Component(entity),
        m_shaderData()
    {
        m_componentType = ComponentType::Shader;

        m_shaderData.fragmentShaderFileName = p_fragmentShaderFileName;
        m_shaderData.vertexShaderFileName = p_vertexShaderFileName;

        ShaderSystem::GetInstance()._initialize(m_shaderData);

    }

    ShaderComponent::~ShaderComponent()
    {

    }

}