#ifndef JEJ_SHADER_SYSTEM_HPP
#define JEJ_SHADER_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>

#include <memory>



namespace jej
{

    class ShaderSystem : public System
    {
        friend class EngineObject;
        friend class Entity;
        friend class ShaderComponent;
        friend class RenderComponent;

    private:

        // Initialize runs through other functions
        void _initialize(detail::ShaderData& p_sd);

        // bind attributes?
        void _bindAttributes(GLuint p_program, const unsigned int p_numAttributes, const std::string& p_attributeName);

        // Load shaders from file and compiles them as usable shader.
        GLuint _loadShader(const std::string& p_shaderDataSource, const GLenum p_type, const detail::ShaderType p_shaderType);

        // Check if user want's to include shaders
        bool _parseShader(const detail::ShaderType p_type, std::string& p_shaderName);

        // Read actual shader files (no matter where they are)
        std::string _readFile(const detail::ShaderType p_type, std::string p_filePath);


        // Enable shader
        void Use(const GLuint& p_program);

        // Disable shader
        void Unuse(const GLuint& p_program);

        //Singleton constructor
        ShaderSystem();

    public:

        //Disabled copy-constructors
        NOCOPY(ShaderSystem);

        //Destructor
        ~ShaderSystem();

        //Returns instance
        static ShaderSystem& GetInstance();


    protected:

        static std::vector<std::shared_ptr<ShaderComponent>> m_components;

        void _update(const float p_deltaTime) override;

        bool _finalize() override;

        bool _initialize() override;

    };

}


#endif