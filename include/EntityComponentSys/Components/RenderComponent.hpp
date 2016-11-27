#ifndef JEJ_RENDER_COMPONENT_HPP
#define JEJ_RENDER_COMPONENT_HPP

//
#include <External/OpenGL_ES2/GLES2/gl2.h>

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
            GLuint shaderProgID = 0u;
            std::vector<GLushort> indices;
            std::vector<GLfloat> vertices;
            std::vector<GLuint> vertexBufferObjects;
            std::vector<GLfloat> colours;
            std::vector<GLfloat> textureCoords;
            GLint indicesBuffer;
            GLint vertexPosBuffer;
            GLint texCoordBuffer;
            void* userData = nullptr;

			//TODO: Add more attribute members as they increase
			GLuint vertexPositionIndex;
			GLuint textureCoordIndex;
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
        RenderComponent(Entity* entity);

        //Constructor for RenderComponent, default-initializes components that were not given
        //Arguments: (order does not matter)
        //ShaderComponent
        //ShapeComponent
        //TransformComponent
        //template <typename ... Args>
        //RenderComponent(Entity& entity, const Args& ... args);

        //Destructor
        ~RenderComponent();

        //Disabled copy-constructors
        RenderComponent(const RenderComponent&) = delete;
        RenderComponent operator=(const RenderComponent&) = delete;


    private:

        std::shared_ptr<ShaderComponent> m_shaderComp;
        std::shared_ptr<ShapeComponent> m_shapeComp;
        std::shared_ptr<TransformComponent> m_transformComp;

        //Struct that holds all data for drawing, see jej::detail::DrawableData for more info
        detail::DrawableData m_myDrawData;
    };

}


#endif