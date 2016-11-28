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

    void RenderComponent::Finalize()
    {
        //Get ShapeType for looping
        ShapeType shapeType = m_shapeComp->m_shapes.at(0)->m_shapeType;

        //Create vertices
        switch (shapeType)
        {
        case jej::ShapeType::Circle:
            break;
        case jej::ShapeType::Rectangle:
            break;
        case jej::ShapeType::Convex:
            break;
        case jej::ShapeType::Triangle:
        {
            //Triangles center of mass (center point) is in TranformComponent->position
            jej::Vector2f centerPoint = m_transformComp->position;

            //Calculate vertices
            //These are constants
            jej::Vector2f first = m_shapeComp->m_shapes.at(0)->GetPoints().at(0);
            jej::Vector2f second = m_shapeComp->m_shapes.at(0)->GetPoints().at(1);
            jej::Vector2f third = m_shapeComp->m_shapes.at(0)->GetPoints().at(2);

            //These are changing
            jej::Vector2f tmpFirst = first;
            jej::Vector2f tmpSecond = second;
            jej::Vector2f tmpThird = third;

            first.x = -tmpSecond.x - tmpThird.x + centerPoint.x * 3.f;
            second.x = -tmpFirst.x - tmpSecond.x +  centerPoint.x * 3.f;
            third.x = -tmpSecond.x - tmpThird.x + centerPoint.x * 3.f;

            first.y = -tmpSecond.y - tmpThird.y + centerPoint.y * 3.f;
            second.y = -tmpFirst.y - tmpSecond.y + centerPoint.y * 3.f;
            third.y = -tmpSecond.y - tmpThird.y + centerPoint.y * 3.f;

            m_myDrawData.vertices.emplace_back(first.x);
            m_myDrawData.vertices.emplace_back(first.y);
            m_myDrawData.vertices.emplace_back(second.x);
            m_myDrawData.vertices.emplace_back(second.y);
            m_myDrawData.vertices.emplace_back(third.x);
            m_myDrawData.vertices.emplace_back(third.y);

            break;
        }

        default:
            break;
        }

        //Create indices

        switch (shapeType)
        {
        case jej::ShapeType::Circle:
            break;

        case jej::ShapeType::Rectangle:
            break;

        case jej::ShapeType::Convex:
            break;

        case jej::ShapeType::Triangle:
        {
            for (int indice = 0; indice < 3; indice++)
                m_myDrawData.indices.emplace_back(indice);
            break;
        }

        default:
            break;
        }


        //Create texture coord

        //Create color

        /////////////////////////////////////////////
        //TODO: Remove this test after work work work
        GLubyte pixels[3 * 3] =
        {
            255, 0, 255,
            127, 0, 127,
            255, 0, 0
        };

        m_myDrawData.textureCoords = 
        {
            -0.5f, 0.0f,
            0.5f, -0.8f,
            0.8f, 0.f
            
        };

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 3, 3, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}