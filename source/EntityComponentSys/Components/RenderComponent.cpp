#include <EntityComponentSys/Components/RenderComponent.hpp>



namespace jej
{
    RenderComponent::RenderComponent()
    {

    }
    //

    RenderComponent::RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp) :
        m_shaderComp(p_shaderComp)
    {
        //TODO: Initialize m_shapeComp and m_transformComp to some defaults
        m_shapeComp = nullptr;
        m_transformComp = nullptr;
    }
    //

    RenderComponent::RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp,
        const std::shared_ptr<ShapeComponent>& p_shapeComp) :
        m_shaderComp(p_shaderComp),
        m_shapeComp(p_shapeComp)
    {
        //TODO: Initialize m_transformComp to some default
        m_transformComp = nullptr;
    }
    //

    RenderComponent::RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp,
        const std::shared_ptr<ShapeComponent>& p_shapeComp,
        const std::shared_ptr<TransformComponent>& p_transformComp) :
        m_shaderComp(p_shaderComp),
        m_shapeComp(p_shapeComp),
        m_transformComp(p_transformComp)
    {

    }
    //

    RenderComponent::~RenderComponent()
    {

    }
}