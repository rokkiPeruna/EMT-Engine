#ifndef JEJ_ENTITY_HPP
#define JEJ_ENTITY_HPP

//
#include <vector>
//

//
#include <EntityComponentSys/Components/Component.hpp>
//

namespace jej
{

    

    class Entity
    {
    public:
        Entity();

        virtual ~Entity();

        template <typename Args>
        bool AddComponent(ComponentType p_compType, Args ... args);

        bool RemoveComponent(ComponentType p_compType);

    private:

        std::vector<Component*> m_components;
    };
}

#endif
