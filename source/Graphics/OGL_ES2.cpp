
#include <Graphics/OGL_ES2.hpp>

#include <Utility/Assert.hpp>
#include <Window/Win32Window.hpp>

namespace jej
{

    OGL_ES2::OGL_ES2(std::shared_ptr<Window>& p_window, const EGLint p_attributeList[]) :
        m_context(EGL_NO_CONTEXT),
        m_display(EGL_NO_DISPLAY),
        m_surface(EGL_NO_SURFACE)
    {
        const bool success = _createContext(p_window, p_attributeList);
        JEJ_ASSERT(success, "Context creation failed.");
    };
    /////////////////////////////////

    OGL_ES2::~OGL_ES2()
    {


    };
    /////////////////////////////////


#ifdef _WIN32
    bool OGL_ES2::_createContext(std::shared_ptr<Window>& p_window, const EGLint p_attributeList[])
    {
        EGLint configs = 0;
        EGLint major = 0;
        EGLint minor = 0;
        EGLContext context = nullptr;
        EGLDisplay display = nullptr;
        EGLSurface surface = nullptr;
        EGLConfig config = nullptr;

        const EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

        if (EGL_NO_DISPLAY == (display = eglGetDisplay(p_window->GetNativeDisplay())))
            return false;
        if (!eglInitialize(display, &major, &minor))
            return false;
        if (!eglGetConfigs(display, NULL, 0, &configs))
            return false;
        if (!eglChooseConfig(display, p_attributeList, &config, 1, &configs))
            return false;
        if (EGL_NO_SURFACE == (surface = eglCreateWindowSurface(display, config, p_window->GetNativeWindow(), NULL)))
            return false;
        if (EGL_NO_CONTEXT == (context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs)))
            return false;
        if (!eglMakeCurrent(display, surface, surface, context))
            return false;

        m_context = context;
        m_display = display;
        m_surface = surface;

        return true;
    }
    /////////////////////////////////

#elif defined ANDROID
    bool OGL_ES2::_createContext(std::shared_ptr<Window> p_window&, const EGLint p_attributeList[], android_app* p_androidApplication)
    {

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

        return true;
    }
#endif
    /////////////////////////////////

    bool OGL_ES2::_draw()
    {
        //

        return true;
    }

    bool OGL_ES2::_drawAll()
    {
        // TODO: Add functionality
        return true;
    }
    /////////////////////////////////

    void OGL_ES2::_swapBuffers()
    {
        eglSwapBuffers(m_display, m_surface);
    }
    /////////////////////////////////

    void OGL_ES2::_updateBuffers(const unsigned int p_index)
    {
        // TODO: Add functionality
    }
    /////////////////////////////////

    void OGL_ES2::_updateBuffersAll()
    {
        // TODO: Add functionality

    }


    }
