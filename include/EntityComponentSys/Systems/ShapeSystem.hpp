#ifndef JEJ_SHAPESYSTEM_HPP
#define JEJ_SHAPESYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>



namespace jej
{

    class ShapeSystem : public System
    {
        //For accessing m_components
		friend class CollisionComponent;
        friend class Entity;
        friend class EngineObject;
        friend class RenderComponent;
        friend class System;

    private:

        //Singleton constructor
        ShapeSystem();

    public:

        ShapeSystem(const ShapeSystem&) = delete;
        ShapeSystem operator=(const ShapeSystem&) = delete;

        //Destructor
        virtual ~ShapeSystem();

        static ShapeSystem& GetInstance();

    protected:

        static std::vector<std::shared_ptr<ShapeComponent>> m_components;

        void _update(const float p_deltaTime) override;

        bool _finalize() override;

        bool _initialize() override;

    };


}


#endif