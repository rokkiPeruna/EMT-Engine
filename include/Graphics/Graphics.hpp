#ifndef JEJ_GRAPHICS_HPP
#define JEJ_GRAPHICS_HPP

#include <OpenGL_ES2/EGL/egl.h>
#include <OpenGL_ES2/EGL/eglplatform.h>
#include <OpenGL_ES2/GLES2/gl2platform.h>

#include <memory>

/////////////////////////////////
namespace jej //NAMESPACE jej
{
    class Graphics : public std::enable_shared_from_this<Graphics>
    {
    public:

        friend class EngineObject;

        // Default values for drawing if not set elswhere
        enum class DEFAULTS
        {
            POSITIONS,
            INDICIES,
            TEXTURE_COORDINATES
        };

        //Short: abstract base class for OpenGL Graphics.
        Graphics();

        //Disabled copy-constructors
        Graphics(const Graphics&) = delete;
        void operator=(const Graphics&) = delete;

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