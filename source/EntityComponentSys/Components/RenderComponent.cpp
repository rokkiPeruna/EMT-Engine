#include <EntityComponentSys/Components/RenderComponent.hpp>



namespace jej
{
    /* RenderComponent::RenderComponent():
         Component(),
         m_shaderComp(nullptr),
         m_shapeComp(nullptr),
         m_transformComp(nullptr)
         {
         m_shaderComp.reset(new ShaderComponent());
         m_shapeComp.reset(new ShapeComponent());
         m_transformComp.reset(new TransformComponent());
         }*/
    //

    RenderComponent::RenderComponent(Entity& entity) :
        Component(entity),
        m_shaderComp(nullptr),
        m_shapeComp(nullptr),
        m_transformComp(nullptr)
    {

        //ShaderComponent
        auto& shaderComps = ShaderSystem::GetInstance().m_components;
        bool shaderDone = false;
        for (unsigned int i = 0u; i < shaderComps.size(); ++i)
        {
            if (shaderComps[i]->m_parentID == entity.m_entityID)
            {
                m_shaderComp = shaderComps[i];
                shaderDone = true;
                break;
            }
        }
        if (!shaderDone)
        {
            entity.AddComponent<ShaderComponent>();
            m_shaderComp = ShaderSystem::GetInstance().m_components.back();
        }

        //ShapeComponent
        auto& shapeComps = ShapeSystem::GetInstance().m_components;
        bool shapeDone = false;
        for (unsigned int i = 0u; i < shapeComps.size(); ++i)
        {
            if (shapeComps[i]->m_parentID == entity.m_entityID)
            {
                m_shapeComp = shapeComps[i];
                shapeDone = true;
                break;
            }
        }
        if (!shapeDone)
        {
            entity.AddComponent<ShapeComponent>();
            m_shapeComp = ShapeSystem::GetInstance().m_components.back();
        }

        //TransformComponent
        auto& transformComps = TransformSystem::GetInstance().m_components;
        bool transformDone = false;
        for (unsigned int i = 0u; i < transformComps.size(); ++i)
        {
            if (transformComps[i]->m_parentID == entity.m_entityID)
            {
                m_transformComp = transformComps[i];
                transformDone = true;
                break;
            }
        }
        if (!transformDone)
        {
            entity.AddComponent<TransformComponent>();
            m_transformComp = TransformSystem::GetInstance().m_components.back();
        }

    }

    RenderComponent::~RenderComponent()
    {

    }
}