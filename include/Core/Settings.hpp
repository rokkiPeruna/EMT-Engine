#include <OpenGL_ES2/EGL/egl.h>
#include <OpenGL_ES2/EGL/eglplatform.h>
#include <OpenGL_ES2/GLES2/gl2platform.h>

namespace jej
{
	namespace settings
	{
        
#ifdef _DEBUG //If debug build

#define ENABLE_ASSERTS
#define JEJ_DEBUG_MODE
#define JEJ_DEBUG_LEVEL 4

#else //If not debug build

#define JEJ_DEBUG_LEVEL 0

#endif //If debug build ends

		
        //Windows GL attributes
#ifdef _WIN32
		static const EGLint attributeList[] =
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

        //Android GL attributes
#elif defined ANDROID
		static const EGLint attributeList[] =
		{
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
		};

#endif
	}
}