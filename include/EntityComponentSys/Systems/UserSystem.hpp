#ifndef JEJ_USERSYSTEM_HPP
#define JEJ_USERSYSTEM_HPP

#include <Core/BaseStructs.hpp>
#include <EntityComponentSys/Entity.hpp>
#include <EntityComponentSys/Systems/System.hpp>
#include <Utility/Messenger.hpp>

#include <tuple>

namespace jej
{

    class UserSystem
    {

    private:

        //Singleton constructor
        UserSystem();

    public:

        //Disabled copy-constructors
        UserSystem(const UserSystem&) = delete;
        UserSystem operator=(const UserSystem&) = delete;

        //Destructor
        ~UserSystem();

        //Get this object
        static UserSystem& GetInstance();

        //Add a component to the given entity
        template<typename T, typename ... Args>
        inline bool AddComponent(Entity& p_entity, const ComponentType p_compType, Args ... p_args);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        T* GetComponentPtr(Entity& p_entity, const ComponentType p_compType);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        const T* GetComponentPtr(const Entity& p_entity, const ComponentType p_compType) const;

        //Check if the entity has a component of the given type
        bool HasComponent(const Entity& p_entity, const ComponentType p_compType);

        //Removes a component of the given type
        bool RemoveComponent(Entity& p_entity, const ComponentType p_compType);

    };

#include <EntityComponentSys/Systems/Inl/UserSystem.inl>

}

#endif