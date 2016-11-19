#ifndef JEJ_ENTITY_HPP
#define JEJ_ENTITY_HPP

#include <Core/BaseStructs.hpp>
#include <Utility/Messenger.hpp>


#include <EntityComponentSys/Components/RenderComponent.hpp>
#include <EntityComponentSys/Components/ShaderComponent.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>
#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Systems/ShaderSystem.hpp>
#include <EntityComponentSys/Systems/TransformSystem.hpp>

//
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
//


namespace jej
{

    class Entity
    {
        //For manipulating components
        friend class Scene;

        //For debugging memory
        friend class EngineObject;

        //For componentIDs
        friend class Component;

    public:

        

        Entity(const std::string& p_name = "");

        Entity(const Entity&) = delete;
        Entity operator=(const Entity&) = delete;

        virtual ~Entity();

        void* userData;

        const unsigned int GetID() const;

        //Components

        //Add a component to the given entity
        template<typename T, typename ... Args>
        T& AddComponent(Args ... p_args);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        T* GetComponentPtr();

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        const T* GetComponentPtr() const;

        //Returns true if the entity has a component of the given type
        template <typename T>
        bool HasComponent();

        //Returns true if Component was successfully removed
        template <typename T>
        bool RemoveComponent();

        //Remove all components from the entity and from corresponding systems
        bool RemoveAllComponents();

    private:

        const std::string m_name;
        const JEJ_COUNT m_entityID;

        static JEJ_COUNT m_entityIDCounter;
        static JEJ_COUNT m_entityIDRemovedCounter;

        std::vector<JEJ_COUNT> m_componentIDs;

    };

#include <EntityComponentSys/Entity/Inl/Entity.inl>

}

#endif
