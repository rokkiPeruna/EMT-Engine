#ifndef JEJ_SCENE_HPP
#define JEJ_SCENE_HPP

#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/Component.hpp>

//For m_components
#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Systems/TransformSystem.hpp>


#include <Utility/Messenger.hpp>

#include <memory>
#include <vector>

namespace jej
{

    class Scene : public std::enable_shared_from_this<Scene>
    {

    public:

        Scene();

        ~Scene();

        std::vector<std::shared_ptr<Entity>>* GetEntities();

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

        template <typename T>
        T* _getComponentPtr(const unsigned int p_ID);

        template <typename T>
        bool _hasComponent(const unsigned int p_ID);

        std::vector<std::shared_ptr<Entity>> m_entities;

    };

#include <Core/Inl/Scene.inl>

}

#endif