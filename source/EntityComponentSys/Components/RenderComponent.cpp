#include <EntityComponentSys/Components/RenderComponent.hpp>

#include <cmath>

namespace jej
{

    RenderComponent::RenderComponent(Entity* p_entity) :
        Component(p_entity),
        m_shaderComp(nullptr),
        m_shapeComp(nullptr),
        m_transformComp(nullptr)
    {

        //ShaderComponent
        auto& shaderComps = ShaderSystem::GetInstance().m_components;
        bool shaderDone = false;
        for (unsigned int i = 0u; i < shaderComps.size(); ++i)
        {
            if (shaderComps[i]->m_parentID == p_entity->m_entityID)
            {
                m_shaderComp = shaderComps[i];
                shaderDone = true;
                break;
            }
        }
        if (!shaderDone)
        {
            p_entity->AddComponent<ShaderComponent>(p_entity);
            m_shaderComp = ShaderSystem::GetInstance().m_components.back();
        }

        //ShapeComponent
        auto& shapeComps = ShapeSystem::GetInstance().m_components;
        bool shapeDone = false;
        for (unsigned int i = 0u; i < shapeComps.size(); ++i)
        {
            if (shapeComps[i]->m_parentID == p_entity->m_entityID)
            {
                m_shapeComp = shapeComps[i];
                shapeDone = true;
                break;
            }
        }
        if (!shapeDone)
        {
            p_entity->AddComponent<ShapeComponent>(p_entity);
            m_shapeComp = ShapeSystem::GetInstance().m_components.back();
        }

        //TransformComponent
        auto& transformComps = TransformSystem::GetInstance().m_components;
        bool transformDone = false;
        for (unsigned int i = 0u; i < transformComps.size(); ++i)
        {
            if (transformComps[i]->m_parentID == p_entity->m_entityID)
            {
                m_transformComp = transformComps[i];
                transformDone = true;
                break;
            }
        }
        if (!transformDone)
        {
            p_entity->AddComponent<TransformComponent>(p_entity);
            m_transformComp = TransformSystem::GetInstance().m_components.back();
        }



    }

    RenderComponent::~RenderComponent()
    {

    }

}