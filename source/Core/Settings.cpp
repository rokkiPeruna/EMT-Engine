#include <Core\Settings.hpp>

namespace jej
{

    namespace settings
    {

#ifdef _WIN32 //Windows GL attributes

        const EGLint Settings::attributeList[] =
        {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, EGL_DONT_CARE,
            EGL_SAMPLE_BUFFERS, 0,
            EGL_NONE
        };


#elif defined __ANDROID__ //Android GL attributes

        const EGLint Settings::attributeList[] =
        {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
        };

#endif


        std::string Settings::rootPath = "";

        std::string Settings::defaultFragmentShaderFileName = "FragmentShaderTexture.frag";

        std::string Settings::defaultVertexShaderFileName = "VertexShader.vert";

        std::string Settings::defaultErrorTextureName = "error.png";

    }

}

#ifdef __ANDROID__

#include <string>
#include <stddef.h>
namespace std
{
    //extern char* strchr(const char*, int);
    //extern int strncmp(const void*, const void*, size_t);
    //extern size_t strlen(const char*);

    char* strstr(const char* s, const char* find)
    {
        const char*p = s;
        const size_t len = strlen(find);
        for(;(p = strchr(p, *find)) != 0; p++)
        {
            if(strncmp(p, find, len) == 0)
                return (char*)p;
        }
        return nullptr;
    }
}

#endif
