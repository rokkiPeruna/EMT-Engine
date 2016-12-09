#ifndef JEJ_SHAPESYSTEM_HPP
#define JEJ_SHAPESYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

#include <EntityComponentSys/Components/TextureComponent.hpp>

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
        friend class TextureSystem;

    private:

        //Singleton constructor
        ShapeSystem();

        bool _setTextureID(const TextureComponent::ShapeData* p_shapeData);

    public:

        //Disabled copy-constructors
        NOCOPY(ShapeSystem);

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