#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Components/RenderComponent.hpp>
#include <Utility/Assert.hpp>



#ifdef _WIN32
#include <Window/Win32Window.hpp>
#elif defined __ANDROID__
#include <Window/AndroidWindow.hpp>
#include <android/log.h>
#include <Core/AndroidAppState.hpp>
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

    }
    //////////////////////////////////////////

    RenderSystem::~RenderSystem()
    {

        if (m_display != EGL_NO_DISPLAY)
            eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_context != EGL_NO_CONTEXT)
            eglDestroyContext(m_display, m_context);

        if (m_surface != EGL_NO_SURFACE)
            eglDestroySurface(m_display, m_surface);

        eglTerminate(m_display);

        m_display = EGL_NO_DISPLAY;
        m_context = EGL_NO_CONTEXT;
        m_surface = EGL_NO_SURFACE;
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
        //If on ANDROID, screen size is given on RenderSystem::_createContext
#ifdef _WIN32
        //Set window's size and offset
        m_winWidth = m_window->GetWinData().sizeX;
        m_winHeight = m_window->GetWinData().sizeY;


        //Set window's size and offset
        m_winWidth = m_window->GetWinData().sizeX;
        m_winHeight = m_window->GetWinData().sizeY;

        m_winOffsetX = m_window->GetWinOSData().offsetX;
        m_winOffsetY = m_window->GetWinOSData().offsetY;
#elif defined __ANDROID__
        m_winOffsetX = 0;
        m_winOffsetY = 0;
#endif
        //Clear color and depth buffer with color
        _clearScreen();

        //Update all changed vertices, etc. some entity has moved
        _updateVertices();

        //Update all vertex buffers, element buffer, etc.
        _drawAllBuffers();

        //Swap front and back buffers
        if (!_swapBuffers())
            Messenger::Add(Messenger::MessageType::Error, "RenderSystem::_swapBuffers failed");
    }
    //////////////////////////////////////////

    void RenderSystem::_clearScreen() const
    {
        glViewport(0, 0, m_winWidth, m_winHeight);
        glClearColor(0.5f, 0.5f, 0.2f, 0.5f);
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

        for (auto& shaperItr : p_rendComp.m_shapeComp->m_shapes)
        {
            //Create alias for ease of use
            auto& drawData = shaperItr->m_myDrawData;

            //Give drawData a shader program ID from p_rendComp's ShaderComponent
            drawData.shaderProgID = p_rendComp.m_shaderComp->m_shaderData.programID;

            //Add attributes' locations, etc. unsigned int index numbers
            //TODO: Add more attribute index queries as attributes increase
            drawData.vertexPositionIndex = glGetAttribLocation(drawData.shaderProgID, "a_position");
            drawData.colorValuesIndex = glGetAttribLocation(drawData.shaderProgID, "a_color");
            drawData.textureCoordIndex = glGetAttribLocation(drawData.shaderProgID, "a_texCoordinate");


            //Indices
            glGenBuffers(1, &drawData.indicesBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.indicesBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawData.indices[0]) * drawData.indices.size(), drawData.indices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            //Texture coordinates
            glGenBuffers(1, &drawData.texCoordBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, drawData.texCoordBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(drawData.textureCoords[0]) * drawData.textureCoords.size(), drawData.textureCoords.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(
                drawData.textureCoordIndex,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                0
                );

            //Positions
            glGenBuffers(1, &drawData.vertexPosBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexPosBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(drawData.vertices[0]) * drawData.vertices.size(), drawData.vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(
                drawData.vertexPositionIndex,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                0
                );

            //Colors
            glGenBuffers(1, &drawData.colorValBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, drawData.colorValBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(drawData.colorValues[0]) * drawData.colorValues.size(), drawData.colorValues.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribPointer(
                drawData.colorValuesIndex,
                4,
                GL_INT,
                GL_TRUE,
                0,
                0
                );

        }
    }
    //////////////////////////////////////////


    bool RenderSystem::_drawAllBuffers()
    {
        for (const auto& itr : m_components)
        {



            //Get shader ID and use that shader and enable attributes
            _useShader(*itr->m_shaderComp);

            for (const auto& shapesItr : itr->m_shapeComp->m_shapes)
            {
                //Create alias of current element's draw data for ease of use
                const auto& drawData = shapesItr->m_myDrawData;

                glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexPosBuffer);
                glVertexAttribPointer(drawData.vertexPositionIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_ARRAY_BUFFER, drawData.texCoordBuffer);
                glVertexAttribPointer(drawData.textureCoordIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_ARRAY_BUFFER, drawData.colorValBuffer);
                glVertexAttribPointer(drawData.colorValuesIndex, 4, GL_BYTE, GL_TRUE, 0, 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);


                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, shapesItr->m_textureID == -1 ? m_defaultTexID : shapesItr->m_textureID);
                glUniform1i(glGetUniformLocation(itr->m_shaderComp->m_shaderData.programID, "sampler_texture"), 0);


                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawData.indicesBuffer);


                //Draw all elements of current RenderComponent
                glDrawElements(
                    GL_TRIANGLES,				            //What type are we drawing, everything is made of triangles so no need to change this!? Maybe triangle stripes
                    drawData.indices.size(),				//How many indices our entity has
                    GL_UNSIGNED_SHORT,			            //What type those indices are, assume we don't have millions of indices in our entity
                    0							            //Normally this is a pointer to indice storage, but because our binding above, this is offset of where to start reading indices, so start at first index
                    );

            }

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
            for (unsigned int i = 0u; i < shaderComp.m_shaderData.numAttribs; i++)
            {
                glEnableVertexAttribArray(i);
            }
        }
        else
        {

            Messenger::Add(Messenger::MessageType::Error, "Shader has zero attributes, shader parent ID: " + std::to_string(shaderComp.m_parentID));
            //No rest for the living - Ee
        }
    }
    //////////////////////////////////////////

    void RenderSystem::_unUseShader(const ShaderComponent& shaderComp) const
    {
        glUseProgram(0);
        if (shaderComp.m_shaderData.numAttribs)
        {
            for (unsigned int i = 0u; i < shaderComp.m_shaderData.numAttribs; i++)
            {
                glDisableVertexAttribArray(i);
            }
        }
        else
        {
            Messenger::Add(Messenger::MessageType::Error, "Shader has zero attributes, shader parent ID: " + std::to_string(shaderComp.m_parentID));
        }
    }
    //////////////////////////////////////////

    void RenderSystem::_bindTexture() const
    {
        //TODO: Add code for texture binding
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

#elif defined __ANDROID__

        EGLint w, h, dummy, format;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;

        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(display, 0, 0);

        // Here, the application chooses the configuration it desires.
        //find the best match if possible, otherwise use the very first one

        eglChooseConfig(display, p_attributeList, nullptr, 0, &numConfigs);
        auto supportedConfigs = new EGLConfig[numConfigs];
        assert(supportedConfigs);
        eglChooseConfig(display, p_attributeList, supportedConfigs, numConfigs, &numConfigs);
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

        surface = eglCreateWindowSurface(display, config, AndroidAppState::m_AppState->window, NULL);
        EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

        context = eglCreateContext(display, config, NULL, contextAttribs);

        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        {
            //Unable to eglMakeCurrent
            return false;
        }

        eglQuerySurface(display, surface, EGL_WIDTH, &w);
        eglQuerySurface(display, surface, EGL_HEIGHT, &h);


        m_winWidth = w;
        m_winHeight = h;

        m_display = display;
        m_surface = surface;
        m_context = context;


        // Check openGL on the system
        auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
        for (auto name : opengl_info) {
            auto info = glGetString(name);
            //LOGI("OpenGL Info: %s", info);
        }
        // Initialize GL state.

        //glEnable(GL_CULL_FACE);
        //glDisable(GL_DEPTH_TEST);

        return true;
#endif

    }
    //////////////////////////////////////////

    bool RenderSystem::_finalize()
    {
        for (auto& itr : m_components)
        {

            for (const auto& shapesItr : itr->m_shapeComp->m_shapes)
            {
                //Create alias for current shape's vertices
                auto& vertices = shapesItr->m_myDrawData.vertices;

                //Create vertices and indices
                switch (shapesItr->m_shapeType)
                {
                case jej::ShapeType::Circle:
                {
                    break;
                }

                case jej::ShapeType::Rectangle:
                {

                    //Create indices, NOTE that DrawableData initialization makes indice 0 for all shapes
                    shapesItr->m_myDrawData.indices.emplace_back(0);
                    shapesItr->m_myDrawData.indices.emplace_back(1);
                    shapesItr->m_myDrawData.indices.emplace_back(2);
                    shapesItr->m_myDrawData.indices.emplace_back(0);
                    shapesItr->m_myDrawData.indices.emplace_back(2);
                    shapesItr->m_myDrawData.indices.emplace_back(3);

                    //Create vertices
                    vertices.emplace_back(shapesItr->m_points.at(0).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(0).y + itr->m_transformComp->position.y);
                    vertices.emplace_back(shapesItr->m_points.at(1).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(1).y + itr->m_transformComp->position.y);
                    vertices.emplace_back(shapesItr->m_points.at(2).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(2).y + itr->m_transformComp->position.y);
                    vertices.emplace_back(shapesItr->m_points.at(3).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(3).y + itr->m_transformComp->position.y);

                    //Give texture coordinates
                    shapesItr->m_myDrawData.textureCoords =
                    {
                        0.0f, -1.f,
                        -1.f, -1.f,
                        -1.f, 0.0f,
                        0.0f, 0.0f
                    };
                    break;
                }

                case jej::ShapeType::Convex:
                {
                    break;
                }

                case jej::ShapeType::Triangle:
                {
                    //Create indices, NOTE that DrawableData initialization makes indice 0 for all shapes
                    for (int indice = 0; indice < 3; indice++)
                        shapesItr->m_myDrawData.indices.emplace_back(indice);

                    //Create vertices
                    vertices.emplace_back(shapesItr->m_points.at(0).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(0).y + itr->m_transformComp->position.y);
                    vertices.emplace_back(shapesItr->m_points.at(1).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(1).y + itr->m_transformComp->position.y);
                    vertices.emplace_back(shapesItr->m_points.at(2).x + itr->m_transformComp->position.x);
                    vertices.emplace_back(shapesItr->m_points.at(2).y + itr->m_transformComp->position.y);

                    //Give texture coordinates
                    shapesItr->m_myDrawData.textureCoords =
                    {
                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f
                    };
                    break;
                }

                case jej::ShapeType::Failed:
                {
                    jej::Messenger::Add(jej::Messenger::MessageType::Error, "Shape had no valid type in RenderSystem::Finalize");
                    break;
                }
                default:
                {
                    break;
                }

                }

            }

            //Create buffers for each this->ShapeComp's Shapetypes
            if (itr->m_shaderComp && itr->m_shapeComp && itr->m_transformComp) //TODO: Re-evaluate this later
                _createBuffersForRenderComponentDrawData(*itr);

        }

        return true;
    }
    //////////////////////////////////////////

    bool RenderSystem::_initialize()
    {
        
        m_window = EngineObject::GetInstance().GetWindowRef();

        if (m_window == nullptr)
        {
            JEJ_ASSERT(false, "Window not initialized");
            return false;
        }

        if (!_createContext(settings::Settings::attributeList))
        {
            JEJ_ASSERT(false, "Context creation failed.");
            return false;
        }

        //Create default texture, texture data can be found in RenderSystem.hpp
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &m_defaultTexID);

        if (m_defaultTexID)
        {
            glBindTexture(GL_TEXTURE_2D, m_defaultTexID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, detail::DefaultTexture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }


        return true;
    }
    //////////////////////////////////////////

    void RenderSystem::_updateVertices()
    {
        for (auto& itr : m_components)
        {
            if (itr->m_transformComp->hasChanged)
            {
                for (const auto& shapesItr : itr->m_shapeComp->m_shapes)
                {
                    //Create alias for current shape's vertices
                    auto* vertices = &shapesItr->m_myDrawData.vertices;

                    //Create alias for shapetype
                    auto& shapeType = shapesItr->m_shapeType;

                    //Create vertices and indices
                    switch (shapesItr->m_shapeType)
                    {
                    case jej::ShapeType::Circle:
                    {
                        break;
                    }

                    case jej::ShapeType::Rectangle:
                    {
                        //Translate local coordinates to global coordinates
                        vertices->at(0) = shapesItr->m_points.at(0).x + itr->m_transformComp->position.x;
                        vertices->at(1) = shapesItr->m_points.at(0).y + itr->m_transformComp->position.y;
                        vertices->at(2) = shapesItr->m_points.at(1).x + itr->m_transformComp->position.x;
                        vertices->at(3) = shapesItr->m_points.at(1).y + itr->m_transformComp->position.y;
                        vertices->at(4) = shapesItr->m_points.at(2).x + itr->m_transformComp->position.x;
                        vertices->at(5) = shapesItr->m_points.at(2).y + itr->m_transformComp->position.y;
                        vertices->at(6) = shapesItr->m_points.at(3).x + itr->m_transformComp->position.x;
                        vertices->at(7) = shapesItr->m_points.at(3).y + itr->m_transformComp->position.y;
                        break;
                    }

                    case jej::ShapeType::Convex:
                    {
                        break;
                    }

                    case jej::ShapeType::Triangle:
                    {

                        vertices->at(0) = shapesItr->m_points.at(0).x + itr->m_transformComp->position.x;
                        vertices->at(1) = shapesItr->m_points.at(0).y + itr->m_transformComp->position.y;
                        vertices->at(2) = shapesItr->m_points.at(1).x + itr->m_transformComp->position.x;
                        vertices->at(3) = shapesItr->m_points.at(1).y + itr->m_transformComp->position.y;
                        vertices->at(4) = shapesItr->m_points.at(2).x + itr->m_transformComp->position.x;
                        vertices->at(5) = shapesItr->m_points.at(2).y + itr->m_transformComp->position.y;
                        break;
                    }

                    case jej::ShapeType::Failed:
                    {
                        jej::Messenger::Add(jej::Messenger::MessageType::Error, "Shape had no valid type in RenderSystem::_updateVertices");
                        break;
                    }

                    default:
                    {
                        break;
                    }

                    }

                    //Alias
                    auto& drawData = shapesItr->m_myDrawData;

                    //Update position vertices buffer
                    glBindBuffer(GL_ARRAY_BUFFER, drawData.vertexPosBuffer);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(drawData.vertices[0]) * drawData.vertices.size(), drawData.vertices.data());
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                }
            }
        }
    }

}