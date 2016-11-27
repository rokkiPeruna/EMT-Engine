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

        //Put every RenderComponent's draw data to buffers 
        for (const auto& itr : m_components)
        {
            if (itr->m_shaderComp && itr->m_shapeComp && itr->m_transformComp) //TODO: Re-evaluate this later
                _createBuffersForRenderComponentDrawData(*itr);
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
        _drawAllBuffers();

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

    void RenderSystem::_clearScreen() const
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


    bool RenderSystem::_swapBuffers() const
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

    void RenderSystem::_createBuffersForRenderComponentDrawData(RenderComponent& p_rendComp)
    {
        //Create alias for ease of use
        auto& drawData = p_rendComp.m_myDrawData;

        //Add attributes' locations, etc. unsigned int index numbers
        //TODO: Add more attribute index queries as attributes increase
        drawData.textureCoordIndex = glGetAttribLocation(drawData.shaderProgID, "vTexCoord");
        drawData.vertexPositionIndex = glGetAttribLocation(drawData.shaderProgID, "vPosition");

        //Indices
        drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.vertexBufferObjects.back());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawData.indices[0]) * drawData.indices.size(), drawData.indices.data(), GL_STATIC_DRAW);
        drawData.indicesBuffer = drawData.vertexBufferObjects.back();


        //Texture coordinates
        drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexBufferObjects.back());
        glBufferData(GL_ARRAY_BUFFER, sizeof(drawData.textureCoords[0]) * drawData.textureCoords.size(), drawData.textureCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(
            drawData.textureCoordIndex,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
            );
        drawData.texCoordBuffer = drawData.vertexBufferObjects.back();

        //Positions
        drawData.vertexBufferObjects.emplace_back(0);
        glGenBuffers(1, &drawData.vertexBufferObjects.back());
        glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexBufferObjects.back());
        glBufferData(GL_ARRAY_BUFFER, sizeof(drawData.vertices[0]) * drawData.vertices.size(), drawData.vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(
            drawData.vertexPositionIndex,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
            );
        drawData.vertexPosBuffer = drawData.vertexBufferObjects.back();

        //Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    //////////////////////////////////////////

    bool RenderSystem::_drawAllBuffers()
    {
        for (auto& itr : m_components)
        {
            //Create alias of current element's draw data for ease of use
            const auto& drawData = itr->m_myDrawData;

            //Get shader ID and use that shader and enable attributes
            _useShader(*itr->m_shaderComp);

            //Bind indices to element array buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.indicesBuffer);


            glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexPosBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, drawData.texCoordBuffer);

            //Init attribute pointers //TODO: If attributes increase, handle this in loop
            glVertexAttribPointer(drawData.vertexPositionIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glVertexAttribPointer(drawData.textureCoordIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

            //TODO: Add call for texture binding once someone creates texture with decent data :D
            //_bindTexture( I take some yet undefined data in me, jee! )

            //Draw all elements of current RenderComponent
            glDrawElements(
                GL_TRIANGLES,				//What type are we drawing, everything is made of triangles so no need to change this!? Maybe triangle stripes
                drawData.indices.size(),	//How many indices our entity has
                GL_UNSIGNED_SHORT,			//What type those indices are, assume we don't have millions of points in our entity
                0							//Normally this is a pointer to indice storage, but because our binding above, this is offset of where to start reading indices, so start at first index
                );


            //Unbind buffers
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            //Unuse shader and disable attributes
            _unUseShader(*itr->m_shaderComp);



        }

        return true;

    }
    //////////////////////////////////////////

    void RenderSystem::_useShader(const ShaderComponent& shaderComp) const
    {
        glUseProgram(shaderComp.m_shaderData.programID);
        if (shaderComp.m_shaderData.numAttribs)
        {
            for (int i = 0; i < shaderComp.m_shaderData.numAttribs; i++)
            {
                glEnableVertexAttribArray(i);
            }
        }
        else
        {
            unsigned int parentID = shaderComp.m_parentID;
            //TODO: Ask Eetu how this works, cause it's midnight and you wanna sleep
            //Messenger::Add(Messenger::MessageType::Error("Shader has zero attributes, shader parent ID: " + parentID));

            Messenger::Add(Messenger::MessageType::Error, "Shader has zero attributes, shader parent ID: " + std::to_string(parentID));
            //No rest for the living - Ee
        }
    }
    //////////////////////////////////////////

    void RenderSystem::_unUseShader(const ShaderComponent& shaderComp) const
    {
        glUseProgram(0);
        if (shaderComp.m_shaderData.numAttribs)
        {
            for (int i = 0; i < shaderComp.m_shaderData.numAttribs; i++)
            {
                glDisableVertexAttribArray(i);
            }
        }
        else
        {
            unsigned int parentID = shaderComp.m_parentID;
            Messenger::Add(Messenger::MessageType::Error, "Shader has zero attributes, shader parent ID: " + std::to_string(parentID));
        }
    }
    //////////////////////////////////////////

    void RenderSystem::_bindTexture() const
    {
        //TODO: Add code for texture binding
    }

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