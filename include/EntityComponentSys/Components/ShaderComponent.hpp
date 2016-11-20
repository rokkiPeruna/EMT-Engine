#ifndef JEJ_SHADER_COMPONENT_HPP
#define JEJ_SHADER_COMPONENT_HPP

#include <string>

//#include <External\OpenGL_ES2\EGL\egl.h>

#include <EntityComponentSys/Components/Component.hpp>

namespace jej
{
    namespace detail
    {
        enum class ShaderType
        {
            Fragment,
            Vertex
        };

        struct ShaderData
        {
            // Actual shader (vertex and fragment combined)
            unsigned int programID = 0u;

            ShaderType type;

            //File names for shaders
            std::string vertexShaderFileName;
            std::string fragmentShaderFileName;

            //For detaching && deleting
            unsigned int fragmentShaderID = 0u;
            unsigned int vertexShaderID = 0u;

            ShaderData(){};
        };
    }

    class ShaderComponent : public Component
    {

        //For deleting shaders
        friend class ShaderSystem;

    public:


        //Constructor
        ShaderComponent::ShaderComponent(Entity& entity, const std::string& p_vertexShaderFileName = "", const std::string& p_fragmentShaderFileName = "");

        //Destructor
        ShaderComponent::~ShaderComponent();

    private:

        detail::ShaderData m_shaderData;



    };

}


#endif