#ifndef JEJ_SCENE_HPP
#define JEJ_SCENE_HPP

#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/Component.hpp>

//For m_components
#include <EntityComponentSys/Systems/System.hpp>

#include <memory>
#include <vector>

namespace jej
{

    class Scene
    {

    public:

        Scene();

        ~Scene();

        std::vector<std::shared_ptr<Entity>>* GetEntities();

        //Components

        //Add a component to the given entity
        template<typename T, typename ... Args>
        inline bool AddComponent(Entity& p_entity, Args ... p_args);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        T* GetComponentPtr(Entity& p_entity);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        template <typename T>
        const T* GetComponentPtr(const Entity& p_entity, const ComponentType p_compType);

        //Check if the entity has a component of the given type
        template <typename T>
        bool HasComponent(const Entity& p_entity);

        //Removes a component of the given type
        template <typename T>
        bool RemoveComponent(Entity& p_entity);

        //Entities

        //Add a component to the given entity
        bool AddEntity(const std::string& p_name = "");

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        Entity* GetEntityPtr(const std::string& p_name);
        Entity* GetEntityPtr(const unsigned int p_ID);

        //Returns pointer to a component of desired type if present on the target entity, otherwise nullptr
        const Entity* GetEntityPtr(const std::string& p_name) const;
        const Entity* GetEntityPtr(const unsigned int p_ID) const;

        //Check if the entity has a component of the given type
        bool HasEntity(const std::string& p_name);
        bool HasEntity(const unsigned int p_ID);

        //Removes a component of the given type
        bool RemoveEntity(const std::string& p_name);
        bool RemoveEntity(const unsigned int p_ID);

    private:

        template <typename T>
        std::vector<std::shared_ptr<T>>& _getComponentVectorFromSystem();

        std::vector<std::shared_ptr<Entity>> m_entities;

    };

#include <Core/Inl/Scene.inl>

}

#endif