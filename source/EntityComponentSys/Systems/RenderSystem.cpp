#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Components/RenderComponent.hpp>
#include <Utility/Assert.hpp>


#ifdef _WIN32
#include <Window/Win32Window.hpp>
#else
#include <Window/AndroidWindow.hpp>
#endif

namespace jej
{
    RenderSystem::RenderSystem() :
        System(),
        m_winWidth(0),
        m_winHeight(0),
        m_winOffsetX(0),
        m_winOffsetY(0),
        m_window(nullptr)
    {
        //Needs work
        m_window.reset(EngineObject::GetInstance().GetWindowRef().get());

        if (!_createContext(settings::attributeList))
            JEJ_ASSERT(false, "Context creation failed.");

    }
    //

    RenderSystem::~RenderSystem()
    {

    }
    //

    RenderSystem& RenderSystem::GetInstance()
    {
        static RenderSystem system;
        return system;
    }
    //

    void RenderSystem::update(const float p_deltaTime)
    {
        //_render();
        _swapBuffers();

        _updateBuffers();
    }


    void RenderSystem::_render()
    {
        _clearScreen();
        return;
    }
    //
    bool RenderSystem::_createContext(const EGLint p_attributeList[])
    {
#ifdef _WIN32
        EGLint configs = 0;
        EGLint major = 0;
        EGLint minor = 0;
        EGLContext context = nullptr;
        EGLDisplay display = nullptr;
        EGLSurface surface = nullptr;
        EGLConfig config = nullptr;

        const EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

        if (EGL_NO_DISPLAY == (display = eglGetDisplay(m_window->GetNativeDisplay())))
            return false;
        if (!eglInitialize(display, &major, &minor))
            return false;
        if (!eglGetConfigs(display, NULL, 0, &configs))
            return false;
        if (!eglChooseConfig(display, p_attributeList, &config, 1, &configs))
            return false;
        if (EGL_NO_SURFACE == (surface = eglCreateWindowSurface(display, config, m_window->GetNativeWindow(), NULL)))
            return false;
        if (EGL_NO_CONTEXT == (context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs)))
            return false;
        if (!eglMakeCurrent(display, surface, surface, context))
            return false;

        m_context = context;
        m_display = display;
        m_surface = surface;

        return true;
        /////////////////////////////////

#elif defined ANDROID

        EGLint w, h, dummy, format;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;

        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(display, 0, 0);

        // Here, the application chooses the configuration it desires.
        //find the best match if possible, otherwise use the very first one

        eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);
        auto supportedConfigs = new EGLConfig[numConfigs];
        assert(supportedConfigs);
        eglChooseConfig(display, attribs, supportedConfigs, numConfigs, &numConfigs);
        assert(numConfigs);
        auto i = 0;
        for (; i < numConfigs; i++)
        {
            auto& cfg = supportedConfigs[i];
            EGLint r, g, b, d;
            if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r) &&
                eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
                eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b) &&
                eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
                r == 8 && g == 8 && b == 8 && d == 0)
            {
                config = supportedConfigs[i];
                break;
            }
        }
        if (i == numConfigs)
            config = supportedConfigs[0];

        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
        surface = eglCreateWindowSurface(display, config, p_androidApplication->window, NULL);

        EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

        context = eglCreateContext(display, config, NULL, contextAttribs);

        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        {
            //Unable to eglMakeCurrent
            return false;
        }

        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);


        win->getWindowDataRef().sizeX = w;
        win->getWindowDataRef().sizeY = h;

        m_display = display;
        m_surface = surface;
        m_context = context;

        win->setApplication(std::make_unique<Application>(reinterpret_cast<Graphics*>(this)));

#endif
        return true;
    }

    void RenderSystem::_clearScreen()
    {
        //If using Win32, set window offsets
#ifdef _WIN32
        glViewport(m_window->GetWinOSData().offsetX, m_window->GetWinOSData().offsetY, m_window->GetWinData().sizeX, m_window->GetWinData().sizeY);
#else
        glViewport(0, 0, m_window->GetWinData().sizeX, m_window->GetWinData().sizeY);
#endif

        glClearColor(0.f, 0.f, 1.f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    //


    bool RenderSystem::_swapBuffers()
    {
        bool success = eglSwapBuffers(m_window->GetNativeDisplay(), m_window->GetNativeWindow());
        return success;
    }

    bool RenderSystem::_updateBuffers()
    {
        return true;

    }
    //
}