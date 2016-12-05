#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys/Components/Component.hpp>
#include <Texture/Shape.hpp>


#include <memory>

namespace jej
{

	class Entity;

    class ShapeComponent : public Component
    {
        //Friend RenderSystem so it can create indices from m_shapes points
        //in SystemFinalize()
        friend class RenderSystem;

    public:

        Vector4i ColorRGBA;

        //Constructor
        ShapeComponent(Entity* p_entity, const Vector4i& p_color = Vector4i(1, 0, 0, 1));

        ShapeComponent(const ShapeComponent&) = delete;
        ShapeComponent operator=(const ShapeComponent&) = delete;

        //Destructor
        virtual ~ShapeComponent();

        //Add a shape to this component
        template <typename ... Args>
        Shape& AddShape(const Args& ... p_args);

        bool RemoveShape(const unsigned int p_ID);


    private:

        std::vector<std::shared_ptr<Shape>> m_shapes;


    };

#include <EntityComponentSys/Components/Inl/ShapeComponent.inl>

}

#endif