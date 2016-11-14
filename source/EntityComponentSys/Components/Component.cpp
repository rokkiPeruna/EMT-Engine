#include <EntityComponentSys/Components/Component.hpp>

#include <Core/EngineObject.hpp>
#include <Core/Scene.hpp>

namespace jej
{

    unsigned int Component::m_componentIDCounter = 0u;
    unsigned int Component::m_componentIDRemovedCounter = 0u;

    Component::Component() :
        m_componentType(),
        m_componentID(++m_componentIDCounter)
    {

    }

    Component::Component(const Component& p_other) :
        m_componentID(++m_componentIDCounter)
    {

    }

    Component& Component::operator=(const Component& p_other)
    {
        m_componentID = ++m_componentIDCounter;
        return *this;
    }

    Component::~Component()
    {
        ++m_componentIDRemovedCounter;
    }
    //

    std::vector<unsigned int>& Component::getComponentIDsRef()
    {
        auto& scene = EngineObject::GetInstance().GetSceneRef();

        auto* entities = scene->GetEntities();

        for (auto itr : *entities)
            if (this->m_componentID == itr->GetID())
                return itr->m_componentIDs;
    }



}