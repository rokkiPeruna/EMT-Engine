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
#include <vector>

namespace jej
{

    namespace detail
    {
        //DrawData holds all data that is needed for drawing single entity
        struct DrawableData
        {
            //DrawableType type = DrawableType::Triangle;
            unsigned int handle = 0u;
            std::vector<GLushort> indices;
            std::vector<GLfloat> vertices;
            std::vector<GLuint> vertexBufferObjects;
            std::vector<GLfloat> colours;
            std::vector<GLfloat> textureCoords;
            GLint indexBuffer;
            GLint vertexPosBuffer;
            GLint texCoordBuffer;
            void* userData = nullptr;
        };
    }
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
        RenderComponent();

        //Constructor for RenderComponent, default-initializes components that were not given
        //Arguments: (order does not matter)
        //ShaderComponent
        //ShapeComponent
        //TransformComponent
        template <typename ... Args>
        RenderComponent(Entity& entity, const Args& ... args);

        //Destructor
        ~RenderComponent();

        //Disabled copy-constructors
        RenderComponent(const RenderComponent&) = delete;
        RenderComponent operator=(const RenderComponent&) = delete;


    private:

        //Create default component
        template <typename T>
        void _createDefault(Entity& p_entity, std::shared_ptr<T>& p_ptr);

        //Tried to add component of wrong type
        template <typename T>
        void _addComponentImpl(Entity& entity, const T& t);

        //Specialized add ShaderComponent
        template <>
        void _addComponentImpl<ShaderComponent>(Entity& entity, const ShaderComponent& t);

        //Specialized add ShapeComponent
        template <>
        void _addComponentImpl<ShapeComponent>(Entity& entity, const ShapeComponent& t);

        //Specialized add TransformComponent
        template <>
        void _addComponentImpl<TransformComponent>(Entity& entity, const TransformComponent& t);

        //Actual separation of var args
        template <typename T, typename ... Args>
        void _addComponentHelper(Entity& entity, const T& t, const Args& ... args);

        //Var args not empty, calls helper to split args
        template <typename ... Args>
        void _addComponent(Entity& entity, const Args& ... args);

        //Var args empty
        template <>
        void _addComponent(Entity& entity);

        //Do nothing if component 't' is already parented to 'entity'
        //Otherwise add the ID of 't' to 'entity'
        template <typename T>
        void _addComponentTrue(Entity& entity, const T& t);

        std::shared_ptr<ShaderComponent> m_shaderComp;
        std::shared_ptr<ShapeComponent> m_shapeComp;
        std::shared_ptr<TransformComponent> m_transformComp;

        //Object's vertex buffer object ID
        detail::DrawableData m_myDrawData;
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


#include <EntityComponentSys/Components/Inl/RenderComponent.inl>

}


#endif