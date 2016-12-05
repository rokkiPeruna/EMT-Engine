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
#include <map>

namespace jej
{

    namespace detail
    {
        //DrawData holds all data that is needed for drawing single entity
        struct DrawableData
        {
            //DrawableType type = DrawableType::Triangle;
            GLuint shaderProgID = 0u;
            std::map<ShapeType, std::vector<GLushort>> indices;
            std::map<ShapeType, std::vector<GLfloat>> vertices;
            std::map<ShapeType, std::vector<GLuint>> vertexBufferObjects;
            std::map<ShapeType, std::vector<GLfloat>> colours;
            std::map<ShapeType, std::vector<GLfloat>> textureCoords;
            std::map<ShapeType, GLint> indicesBuffer;
            std::map<ShapeType, GLint> vertexPosBuffer;
            std::map<ShapeType, GLint> texCoordBuffer;
            void* userData = nullptr;

            //TODO: Add more attribute members as they increase
            GLuint vertexPositionIndex;
            GLuint textureCoordIndex;

            NOCOPY(DrawableData);
            ~DrawableData(){};
            //Default constuctor, initializes map-containers with correct key-value pairs
            DrawableData()
            {


                indices.insert(std::make_pair(ShapeType::Triangle, std::vector<GLushort>{0}));
                indices.insert(std::make_pair(ShapeType::Rectangle, std::vector<GLushort>{0}));
                indices.insert(std::make_pair(ShapeType::Circle, std::vector<GLushort>{0}));
                indices.insert(std::make_pair(ShapeType::Convex, std::vector<GLushort>{0}));

                vertices.insert(std::make_pair(ShapeType::Triangle, std::vector<GLfloat>{0}));
                vertices.insert(std::make_pair(ShapeType::Rectangle, std::vector<GLfloat>{0}));
                vertices.insert(std::make_pair(ShapeType::Circle, std::vector<GLfloat>{0}));
                vertices.insert(std::make_pair(ShapeType::Convex, std::vector<GLfloat>{0}));

                vertexBufferObjects.insert(std::make_pair(ShapeType::Triangle, std::vector<GLuint>{0}));
                vertexBufferObjects.insert(std::make_pair(ShapeType::Rectangle, std::vector<GLuint>{0}));
                vertexBufferObjects.insert(std::make_pair(ShapeType::Circle, std::vector<GLuint>{0}));
                vertexBufferObjects.insert(std::make_pair(ShapeType::Convex, std::vector<GLuint>{0}));

                colours.insert(std::make_pair(ShapeType::Triangle, std::vector<GLfloat>{0}));
                colours.insert(std::make_pair(ShapeType::Rectangle, std::vector<GLfloat>{0}));
                colours.insert(std::make_pair(ShapeType::Circle, std::vector<GLfloat>{0}));
                colours.insert(std::make_pair(ShapeType::Convex, std::vector<GLfloat>{0}));

                textureCoords.insert(std::make_pair(ShapeType::Triangle, std::vector<GLfloat>{0}));
                textureCoords.insert(std::make_pair(ShapeType::Rectangle, std::vector<GLfloat>{0}));
                textureCoords.insert(std::make_pair(ShapeType::Circle, std::vector<GLfloat>{0}));
                textureCoords.insert(std::make_pair(ShapeType::Convex, std::vector<GLfloat>{0}));

                indicesBuffer.insert(std::make_pair(ShapeType::Triangle, 0));
                indicesBuffer.insert(std::make_pair(ShapeType::Rectangle, 0));
                indicesBuffer.insert(std::make_pair(ShapeType::Circle, 0));
                indicesBuffer.insert(std::make_pair(ShapeType::Convex, 0));

                vertexPosBuffer.insert(std::make_pair(ShapeType::Triangle, 0));
                vertexPosBuffer.insert(std::make_pair(ShapeType::Rectangle, 0));
                vertexPosBuffer.insert(std::make_pair(ShapeType::Circle, 0));
                vertexPosBuffer.insert(std::make_pair(ShapeType::Convex, 0));

                texCoordBuffer.insert(std::make_pair(ShapeType::Triangle, 0));
                texCoordBuffer.insert(std::make_pair(ShapeType::Rectangle, 0));
                texCoordBuffer.insert(std::make_pair(ShapeType::Circle, 0));
                texCoordBuffer.insert(std::make_pair(ShapeType::Convex, 0));
            }
        };
    }

    //Forward declarations
    class ShaderComponent;
    class TransformComponent;
    class ShapeComponent;
	class Entity;
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

        //Disabled copy-constructors
        NOCOPY(RenderComponent);

        //Destructor
        ~RenderComponent();



        void Finalize();


    private:

        std::shared_ptr<ShaderComponent> m_shaderComp;
        std::shared_ptr<ShapeComponent> m_shapeComp;
        std::shared_ptr<TransformComponent> m_transformComp;

        //Struct that holds all data for drawing, see jej::detail::DrawableData for more info
        detail::DrawableData m_myDrawData;

        
    };

}


#endif