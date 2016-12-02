#include <EntityComponentSys/Entity/Entity.hpp>

#include <Core/EngineObject.hpp>

//#include <EntityComponentSys/Systems/TransformSystem.hpp>

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
    //

    Entity::~Entity()
    {
        ++m_entityIDRemovedCounter;

        //Entity takes care of it's components
        RemoveAllComponents();
    }
    //

    const JEJ_COUNT Entity::GetID() const
    {
        return m_entityID;
    }

    namespace
    {
        size_t _getSize()
        {
            return 
        }
    }


    bool Entity::RemoveAllComponents()
    {


        auto& engine = EngineObject::GetInstance();

        auto koo = std::tuple_size<engine.m_systems>::value;

        size_t koko = engine.m_systems_Mysize();



        detail::ForTuple(EngineObject::GetInstance().m_systems, RemoveComponent<>());

        //TODO: Call remove on all types
        RemoveComponent<RenderComponent>();
        RemoveComponent<ShaderComponent>();
        RemoveComponent<ShapeComponent>();
        RemoveComponent<TextureComponent>();
        RemoveComponent<TransformComponent>();


        if (m_componentIDs.empty())
            return true;
        return false;
    }

}