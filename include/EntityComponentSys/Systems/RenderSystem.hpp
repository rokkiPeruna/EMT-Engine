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
    //Forward declarating Window-class etc.
    class Window;
    class RenderComponent;
    class ShaderComponent;
    class ShapeComponent;
    class SpriteComponent;
    //

    namespace detail
    {
        struct _VBO
        {

        };
    }

    class RenderSystem : public System
    {

		//For manipulating m_components
		friend class EngineObject;
		friend class Entity;
        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
        
        


    private:

        //Constructor is private for singleton
        RenderSystem();

    public:

        //Disabled copy-constructors
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem operator=(const RenderSystem&) = delete;

        //Destructor
        ~RenderSystem();

        //Create instance of class
        static RenderSystem& GetInstance();

        void _render();
		

    private:
        
        //Screen properties for OpenGL ES
        unsigned int m_winWidth;
        unsigned int m_winHeight;
        unsigned int m_winOffsetX;
        unsigned int m_winOffsetY;

        //Smart pointer to Window - singleton
        std::shared_ptr<Window> m_window;

        //Vector containing draw data for each to-draw entity
        std::vector<DrawableData> m_myDrawables;

        //This renders and draws every RenderComponent by calling priv methods
        void _createBuffers();

        void _update(const float p_deltaTime) override;

        //
        void _clearScreen();

        //
        bool _swapBuffers();

        //
        bool _updateBuffers();

        //
        void _useShader(ShaderComponent& shaderComp);

        //
        void _unUseShader(ShaderComponent& shaderComp);

        //////////////////////////////
        //Methods and variables for OpenGL ES initialization
        EGLContext m_context;
        EGLDisplay m_display;
        EGLSurface m_surface;

        bool _createContext(const EGLint p_attributeList[]);

        //Vertex buffer objects for various different types
        //TODO: Add buffers


        static std::vector<std::shared_ptr<RenderComponent>> m_components;

    };
}

#endif