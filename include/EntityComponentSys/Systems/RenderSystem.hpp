#ifndef JEJ_RENDER_SYSTEM_HPP
#define JEJ_RENDER_SYSTEM_HPP

//
#include <EntityComponentSys/Systems/System.hpp>
//

//
#include <memory>
#include <assert.h>
//

//
#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>
//

namespace jej
{

    namespace detail
    {
        static GLubyte DefaultTexture[4 * 4 * 3] = //Width * Height * RGB
        {
            255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
            0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0,
            0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255,
            0, 150, 150, 0, 150, 150, 0, 150, 150, 0, 150, 150
        };
    }



    //Forward declarating Window-class etc.
    class Window;
    class RenderComponent;
    class ShaderComponent;
    class ShapeComponent;
    class TextureComponent;
    //

    class RenderSystem : public System
    {

        //For manipulating m_components
        friend class EngineObject;
        friend class Entity;

#ifdef _WIN32
        //For allowing Win32 event handler to call _update() in WM_PAINT
        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

#elif defined __ANDROID__
        friend void engine_handle_cmd(struct android_app* app, int32_t cmd);
        friend class AndroidWindow;
#endif

    private:

        //Constructor is private for singleton
        RenderSystem();

    public:

        //Disabled copy-constructors
        NOCOPY(RenderSystem);

        //Destructor
        ~RenderSystem();

        //Create instance of class
        static RenderSystem& GetInstance();


    private:

        //Screen properties for OpenGL ES
        unsigned int m_winWidth;
        unsigned int m_winHeight;
        unsigned int m_winOffsetX;
        unsigned int m_winOffsetY;

        //Smart pointer to Window - singleton
        std::shared_ptr<Window> m_window;

        //Method for initializing RenderComponent's draw data
        void _createBuffersForRenderComponentDrawData(RenderComponent& p_rendComp);

        //This system's update that gets called from WM_PAINT in Win32Window - class
        void _update(const float p_deltaTime) override;

        //
        void _clearScreen() const;

        //
        bool _swapBuffers() const;

        //
        bool _drawAllBuffers();

        //
        void _useShader(const ShaderComponent& shaderComp) const;

        //
        void _unUseShader(const ShaderComponent& shaderComp) const;

        //
        void _bindTexture() const;



        //////////////////////////////
        //Methods and variables for OpenGL ES initialization
        EGLContext m_context;
        EGLDisplay m_display;
        EGLSurface m_surface;

        //Initialize Open GL ES 2.0
        bool _createContext(const EGLint p_attributeList[]);


        void _render();


    protected:



        //Holds shared pointers to all RenderComponents
        static std::vector<std::shared_ptr<RenderComponent>> m_components;

        bool _finalize() override;

        bool _initialize() override;

        GLuint m_defaultTexID;
    };
}

#endif