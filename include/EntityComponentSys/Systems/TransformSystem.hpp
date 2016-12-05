#ifndef JEJ_TRANSFORM_SYSTEM_HPP
#define JEJ_TRANSFORM_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{

    //For m_components
    class TransformComponent;

    class TransformSystem : public System
    {

        //For accessing m_components
        friend class Entity;
        friend class EngineObject;
        friend class System;
        friend class RenderComponent;

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

        bool _finalize() override;

        bool _initialize() override;


    };

}

#endif