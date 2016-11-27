#include <Core\Settings.hpp>

namespace jej
{

    namespace settings
    {

#ifdef _WIN32 //Windows GL attributes

        const EGLint attributeList[] =
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


#elif defined ANDROID //Android GL attributes

        const EGLint attributeList[] =
        {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
        };

#endif


        std::string rootPath = "";

        std::string defaultFragmentShaderFileName = "FragmentShaderTexture.frag";

        std::string defaultVertexShaderFileName = "VertexShader.vert";

    }

}

