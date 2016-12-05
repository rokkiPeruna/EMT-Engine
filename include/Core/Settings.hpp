#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2platform.h>

#include <string>

namespace jej
{
    namespace settings
    {

#ifdef _DEBUG //If debug build

#define JEJ_ENABLE_ASSERTS
#define JEJ_DEBUG_MODE
#define JEJ_DEBUG_LEVEL 4

#else //If not debug build

#define JEJ_DEBUG_LEVEL 0

#endif //If debug build ends

        //GL attributes
        extern const EGLint attributeList[];


        //Path to executable
        extern std::string rootPath;

        extern std::string defaultFragmentShaderFileName;

        extern std::string defaultVertexShaderFileName;

    }


#define NOCOPY(className) \
    className(const className&) = delete; \
    void operator=(const className&) = delete; \
    className(className&&) = delete


}