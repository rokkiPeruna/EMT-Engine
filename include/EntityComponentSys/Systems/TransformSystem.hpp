#ifndef JEJ_TRANSFORM_SYSTEM_HPP
#define JEJ_TRANSFORM_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{

    //For m_components
    class TransformComponent;

    class TransformSystem : public System
    {

        //For modifying m_components
        friend class Entity;

        //For modifying m_components
        friend class System;

    private:

        TransformSystem();

    public:

        static TransformSystem& GetInstance();

        TransformSystem(const TransformSystem&) = delete;
        TransformSystem operator=(const TransformSystem&) = delete;

        virtual ~TransformSystem();

    protected:

        void _update(const float deltaTime) override;

        static std::vector<std::shared_ptr<TransformComponent>> m_components;

        

    };

}

#endif