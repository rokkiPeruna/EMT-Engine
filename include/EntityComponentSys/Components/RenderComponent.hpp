#ifndef JEJ_RENDER_COMPONENT_HPP
#define JEJ_RENDER_COMPONENT_HPP


//
#include <EntityComponentSys/Components/Component.hpp>
//

//
#include <memory>

namespace jej
{
    //Forward declarations
    class ShaderComponent;
    class TransformComponent;
    class ShapeComponent;
    //

    //RenderComponent class is basically wrapper for other components that are needed
    //for displaying drawable entities on screen
    class RenderComponent
        :public Component
    {
        //Friending RenderSystem so it can access key values for rendering
        //through shared pointers in render components
        friend RenderSystem;

    public:
        //Default constructor
        RenderComponent();

        //Constructor for user given ShaderComponent, default initializes
        //TransformComponent and ShapeComponent
        RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp);

        //Constructor for user given ShaderComponent and ShapeComponent,
        //default initializes ShapeComponent
        RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp,
            const std::shared_ptr<ShapeComponent>& p_shapeComp);

        //Constructor for user given ShaderComponent, ShapeComponent and TransformComponent
        RenderComponent(const std::shared_ptr<ShaderComponent>& p_shaderComp,
            const std::shared_ptr<ShapeComponent>& p_shapeComp,
            const std::shared_ptr<TransformComponent>& p_transformComp);

        //Destructor
        ~RenderComponent();

        //Disabled copy-constructors
        RenderComponent(const RenderComponent&) = delete;
        RenderComponent operator=(const RenderComponent&) = delete;


    private:

        std::shared_ptr<ShaderComponent> m_shaderComp;
        std::shared_ptr<ShapeComponent> m_shapeComp;
        std::shared_ptr<TransformComponent> m_transformComp;
    };
}


#endif