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
    std::vector<std::shared_ptr<RenderComponent>> RenderSystem::m_components = {};


    RenderSystem::RenderSystem() :
        System(),
        m_winWidth(0),
        m_winHeight(0),
        m_winOffsetX(0),
        m_winOffsetY(0),
        m_window(nullptr),
        m_context(0),
        m_display(0),
        m_surface(0)

    {

#ifdef _WIN32
        m_window = std::static_pointer_cast<Win32Window>(EngineObject::GetInstance().GetWindowRef());
#elif defined ANDROID
        m_window = std::static_pointer_cast<AndroidWindow>(EngineObject::GetInstance().GetWindowRef());
#endif
        assert(m_window != nullptr);
        if (!_createContext(settings::attributeList))
            JEJ_ASSERT(false, "Context creation failed.");

        //Initialize DrawData
        for (const auto& itr : m_components)
        {
            //Put component's vertice data to vertices vector
            //by iterating through shapeComp's different shapes
            for (const auto& m_shapes_itr : itr->m_shapeComp->m_shapes)
            {
                //m_drawData.vertices.emplace_back(m_shapes_itr->GetPoints());

                //Check for nullptr
                if (m_shapes_itr)
                {
                    //Shape can consist of multiple shapes, etc. triangles, quads, circles
                    //so iterate each shape and get their points
                    for (const auto& m_points_itr : m_shapes_itr->GetPoints())
                    {
                        m_drawData.vertices.push_back(m_points_itr.x);
                        m_drawData.vertices.push_back(m_points_itr.y);
                    }
                }
            }//Now DrawData struct contains all RenderComponent's vertices (x, y)


            

        }


    }
    //////////////////////////////////////////

    RenderSystem::~RenderSystem()
    {

    }
    //////////////////////////////////////////

    RenderSystem& RenderSystem::GetInstance()
    {
        static RenderSystem system;
        return system;
    }
    //////////////////////////////////////////

    void RenderSystem::_update(const float p_deltaTime)
    {
        //Set window's size and offset
        m_winWidth = m_window->GetWinData().sizeX;
        m_winHeight = m_window->GetWinData().sizeY;

#ifdef _WIN32
        m_winOffsetX = m_window->GetWinOSData().offsetX;
        m_winOffsetY = m_window->GetWinOSData().offsetY;
#elif defined __ANDROID__
        m_winOffsetX = 0;
        m_winOffsetY = 0;
#endif

        //Clear color and depth buffer with color
        _clearScreen();

        //Update all vertex buffers, element buffer, etc.
        _updateBuffers();

        //Swap front and back buffers
        if (!_swapBuffers())
            Messenger::Add(Messenger::MessageType::Error, "RenderSystem::_swapBuffers failed");

    }
    //////////////////////////////////////////

    void RenderSystem::_render()
    {
        _clearScreen();
        return;
    }
    //////////////////////////////////////////

    //////////////////////////////////////////

    void RenderSystem::_clearScreen()
    {
        //eglMakeCurrent(m_display, m_surface, m_surface, m_context);

        //If using Win32, set window offsets
        //glViewport(m_window->GetWinOSData().offsetX, m_window->GetWinOSData().offsetY, m_window->GetWinData().sizeX, m_window->GetWinData().sizeY);
        glViewport(m_winOffsetX, m_winOffsetY, m_winWidth, m_winHeight);
        //glViewport(0, 0, m_winWidth, m_winHeight);

        glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    //////////////////////////////////////////


    bool RenderSystem::_swapBuffers()
    {

        GLint success = eglSwapBuffers(m_display, m_surface);

        switch (success)
        {
        case EGL_FALSE:             break;
        case EGL_BAD_DISPLAY:       break;
        case EGL_NOT_INITIALIZED:   break;
        case EGL_BAD_SURFACE:       break;
        case EGL_CONTEXT_LOST:      break;
        default:
            break;
        }

        return (GL_TRUE == success) ? true : false;
    }
    //////////////////////////////////////////

    void RenderSystem::_createBuffers()
    {
        //Indices
        m_drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &m_drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawData.vertexBufferObjects.back());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_drawData.indices[0]) * m_drawData.indices.size(), m_drawData.indices.data(), GL_STATIC_DRAW);
        m_drawData.indexBuffer = m_drawData.vertexBufferObjects.back();


        //Texture coordinates
        m_drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &m_drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ARRAY_BUFFER, m_drawData.vertexBufferObjects.back());
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_drawData.textureCoords[0]) * m_drawData.textureCoords.size(), m_drawData.textureCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(
        textureCoordIndex,
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        0, 
        0
        );
        m_drawData.texCoordBuffer = m_drawData.vertexBufferObjects.back();

        //Positions
        m_drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &m_drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ARRAY_BUFFER, m_drawData.vertexBufferObjects.back());
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_drawData.vertices[0]) * m_drawData.vertices.size(), m_drawData.vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(vertexPosIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        m_drawData.vertexPosBuffer = m_drawData.vertexBufferObjects.back();

        //Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    //////////////////////////////////////////

    bool RenderSystem::_updateBuffers()
    {
        for (auto& it : m_components)
        {
            //Get shader ID and use that shader
            _useShader(*it->m_shaderComp);

            //Bind buffer object
            glBindBuffer(GL_ARRAY_BUFFER, it->m_vboID);

            for (int i = 0; it->m_shaderComp->m_shaderData.numAttribs; i++)
            {
                glVertexAttribPointer(
                    i,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(Vertex),
                    (void*)offsetof(Vertex, position)
                    );

            }


            //Unuse shader
            _unUseShader(*it->m_shaderComp);


            break;
        }

        return true;

    }
    //////////////////////////////////////////

    void RenderSystem::_useShader(ShaderComponent& shaderComp)
    {
        glUseProgram(shaderComp.m_shaderData.programID);
        for (int i = 0; i < shaderComp.m_shaderData.numAttribs; i++)
        {
            glEnableVertexAttribArray(i);
        }
    }
    //////////////////////////////////////////

    void RenderSystem::_unUseShader(ShaderComponent& shaderComp)
    {
        glUseProgram(0);
        for (int i = 0; i < shaderComp.m_shaderData.numAttribs; i++)
        {
            glDisableVertexAttribArray(i);
        }
    }
    //////////////////////////////////////////

    bool RenderSystem::_createContext(const EGLint p_attributeList[])
    {
#ifdef _WIN32
        EGLint configs = 0;
        EGLint major = 0;
        EGLint minor = 0;
        EGLConfig config = nullptr;

        const EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

        if (EGL_NO_DISPLAY == (m_display = eglGetDisplay(m_window->GetNativeDisplay())))
            return false;
        if (!eglInitialize(m_display, &major, &minor))
            return false;
        if (!eglGetConfigs(m_display, NULL, 0, &configs))
            return false;
        if (!eglChooseConfig(m_display, p_attributeList, &config, 1, &configs))
            return false;
        if (EGL_NO_SURFACE == (m_surface = eglCreateWindowSurface(m_display, config, m_window->GetNativeWindow(), NULL)))
            return false;
        if (EGL_NO_CONTEXT == (m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttribs)))
            return false;
        if (!eglMakeCurrent(m_display, m_surface, m_surface, m_context))
            return false;

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

        return true;
#endif

    }
    //////////////////////////////////////////
}