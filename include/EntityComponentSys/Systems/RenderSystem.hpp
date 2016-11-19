#ifndef JEJ_RENDER_SYSTEM_HPP
#define JEJ_RENDER_SYSTEM_HPP

//
#include <EntityComponentSys/Systems/System.hpp>
//

//
#include <memory>
//

//
#include <External/OpenGL_ES2/EGL/egl.h>
//

namespace jej
{
    //Forward declarating Window-class etc.
    class Window;
    class RenderComponent;
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
        short int m_winWidth;
        short int m_winHeight;
        short int m_winOffsetX;
        short int m_winOffsetY;

        //Smart pointer to Window - singleton
        std::shared_ptr<Window> m_window;

        //

        //
        void _clearScreen();

        //
        bool _swapBuffers();

        //
        bool _updateBuffers();


        //////////////////////////////
        //Methods and variables for OpenGL ES initialization
        EGLContext m_context;
        EGLDisplay m_display;
        EGLSurface m_surface;

        bool _createContext(const EGLint p_attributeList[]);

        //Vertex buffer objects for various different types

    protected:

        //This renders and draws every RenderComponent by calling priv methods
        void _update(const float p_deltaTime) override;

        static std::vector<std::shared_ptr<RenderComponent>> m_components;

    };
}

#endif