#include <EntityComponentSys/Entity/Entity.hpp>

#include <Core/EngineObject.hpp>


namespace jej
{

    unsigned int Entity::m_entityIDCounter = 0u;
    unsigned int Entity::m_entityIDRemovedCounter = 0u;

    Entity::Entity(const std::string& p_name) :
        m_name(p_name),
        m_entityID(++m_entityIDCounter),
        userData(nullptr)
    {

    }
    ////////////////////////////////////////////


    Entity::~Entity()
    {
        ++m_entityIDRemovedCounter;

        //Entity takes care of it's components
        RemoveAllComponents();
    }
    ////////////////////////////////////////////


    const JEJ_COUNT Entity::GetID() const
    {
        return m_entityID;
    }
    ////////////////////////////////////////////


    bool Entity::RemoveAllComponents()
    {
        //Current development environment does not support required features to do the following with meta-template-programming - Ee

        //TODO: Call remove on all types
        RemoveComponent<RenderComponent>();
        RemoveComponent<ShaderComponent>();
        RemoveComponent<ShapeComponent>();
        RemoveComponent<TextureComponent>();
        RemoveComponent<TransformComponent>();

        if (m_componentIDs.empty())
            return true;
         
        JEJ_ASSERT(false, "Not all components removed!");
        Messenger::Add(Messenger::MessageType::Warning, "Not all components removed from entity: ", m_name);
        return false;
    }
    ////////////////////////////////////////////


}