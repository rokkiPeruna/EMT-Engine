#ifndef JEJ_GRAPHICS_HPP
#define JEJ_GRAPHICS_HPP

#include <Core/Settings.hpp>

#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2platform.h>

#include <memory>

/////////////////////////////////
namespace jej //NAMESPACE jej
{
    class Graphics
    {
    public:

        friend class EngineObject;

        // Default values for drawing if not set elswhere
        enum class DEFAULTS
        {
            POSITIONS,
            INDICES,
            TEXTURE_COORDINATES
        };

        //Short: abstract base class for OpenGL Graphics.
        Graphics();

        //Disabled copy-constructors
        NOCOPY(Graphics);

        //Destructor
        virtual ~Graphics();

    protected:


        virtual bool _draw() = 0;

        virtual bool _drawAll() = 0;

        // eglSwapBuffers posts its color buffer to the associated native window
        virtual void _swapBuffers() = 0;

        virtual void _updateBuffers(const unsigned int) = 0;

        virtual void _updateBuffersAll() = 0;

    };

}
#endif // NAMESPACE jej