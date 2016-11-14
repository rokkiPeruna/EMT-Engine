#ifndef JEJ_ENTITY_HPP
#define JEJ_ENTITY_HPP

#include <Core/BaseStructs.hpp>
#include <Utility/Messenger.hpp>


//
#include <memory>
#include <string>
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
        template<typename ... Args>
        inline bool AddComponent(const ComponentType p_type, Args ... p_args);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        T* GetComponentPtr(const ComponentType p_type);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        const T* GetComponentPtr(const ComponentType p_type) const;

        //Returns true if the entity has a component of the given type
        bool HasComponent(const ComponentType p_type);


        //Returns true if Component was successfully removed
        bool RemoveComponent(const ComponentType p_type);

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
