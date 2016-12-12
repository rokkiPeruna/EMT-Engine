#ifndef JEJ_SETTINGS_HPP
#define JEJ_SETTINGS_HPP

#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2platform.h>

#include <string>


#ifdef _DEBUG //If debug build

#define JEJ_ENABLE_ASSERTS
#define JEJ_DEBUG_MODE
#define JEJ_DEBUG_LEVEL 4

#else //If not debug build

#define JEJ_DEBUG_LEVEL 0

#endif //If debug build ends


#define NOCOPY(className) \
    className(const className&) = delete; \
    void operator=(const className&) = delete; \
    className(className&&) = delete




namespace jej
{

    namespace settings
    {

        class Settings
        {
        private:

            Settings() = delete;
            NOCOPY(Settings);
            ~Settings() = delete;

        public:

            //GL attributes
            static const EGLint attributeList[];

            //Path to executable
            static std::string rootPath;

            //Default fragment shader file name with extension
            static std::string defaultFragmentShaderFileName;

            //Default vertex shader file name with extension
            static std::string defaultVertexShaderFileName;

            //Default error texture file name with extension
            static std::string defaultErrorTextureName;

        };

    }

}

#include <Core/Inl/Settings.inl>

#endif

#ifdef __ANDROID__

namespace std
{
    char* strstr(const char* s, const char* find);
}

#endif