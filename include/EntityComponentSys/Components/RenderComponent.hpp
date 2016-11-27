#ifndef JEJ_RENDER_COMPONENT_HPP
#define JEJ_RENDER_COMPONENT_HPP


//
#include <EntityComponentSys/Components/Component.hpp>
//

//#include <EntityComponentSys/Entity/Entity.hpp>

#include <Core/Scene.hpp>
#include <EntityComponentSys/Components/ShaderComponent.hpp>
#include <EntityComponentSys/Components/ShapeComponent.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <Utility/Assert.hpp>
#include <Utility/Messenger.hpp>

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
    class RenderComponent : public Component
    {
        //Friending RenderSystem so it can access key values for rendering
        //through shared pointers in render components
        friend class RenderSystem;

    public:
        //Default constructor
        RenderComponent(Entity& entity);

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


    //template<typename T>
    //void loadBrush_sub_impl()
    //{
    //    // do some work here
    //}

    //template<typename... Targs>
    //void loadBrush_sub();

    //template<typename T, typename... V>
    //void loadBrush_sub_helper()
    //{
    //    loadBrush_sub_impl<T>();
    //    loadBrush_sub<V...>();
    //}

    //template<typename... Targs>
    //void loadBrush_sub()
    //{
    //    loadBrush_sub_helper<Targs...>();
    //}

    //template<>
    //void loadBrush_sub<>()
    //{
    //}


}


#endif