#include <Core/Settings.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/FileHandler.hpp>

#include <EntityComponentSys/Systems/ShaderSystem.hpp>

#ifdef __ANDROID__
#include <Core/AndroidAppState.hpp>
#endif

#include <vector>
namespace jej
{
    std::vector<std::shared_ptr<ShaderComponent>> ShaderSystem::m_components = {};



    ShaderSystem::ShaderSystem()
    {

    }
    //////////////////////////////////////////

    ShaderSystem::~ShaderSystem()
    {
        //Delete shaders from GPU
        for (auto itr : m_components)
        {
            if (itr->m_shaderData.fragmentShaderID != 0u)
            {
                glDetachShader(itr->m_shaderData.programID, itr->m_shaderData.fragmentShaderID);
                glDeleteShader(itr->m_shaderData.fragmentShaderID);
            }
            if (itr->m_shaderData.vertexShaderID != 0u)
            {
                glDetachShader(itr->m_shaderData.programID, itr->m_shaderData.vertexShaderID);
                glDeleteShader(itr->m_shaderData.vertexShaderID);
            }
        }
    }
    //////////////////////////////////////////

    ShaderSystem& ShaderSystem::GetInstance()
    {
        static ShaderSystem system;
        return system;
    }
    //////////////////////////////////////////


    void ShaderSystem::_initialize(detail::ShaderData& p_sd)
    {

        if (!_parseShader(detail::ShaderType::Fragment, p_sd.fragmentShaderFileName)){}
            //TODO: Android problem //Messenger::Add(Messenger::MessageType::Error, "Failed to parse fragment shader ");

        if (!_parseShader(detail::ShaderType::Vertex, p_sd.vertexShaderFileName)){}
            //TODO: Android problem //Messenger::Add(Messenger::MessageType::Error, "Failed to parse vertex shader ");

        if (!(p_sd.programID = glCreateProgram()))
        {
            //TODO: Android problem //Messenger::Add(Messenger::MessageType::Error, "Failed to create GL program");
            return;
        }

        GLuint fragmentShader = _loadShader((p_sd.fragmentShaderFileName), GL_FRAGMENT_SHADER, detail::ShaderType::Fragment);
        GLuint vertexShader = _loadShader((p_sd.vertexShaderFileName), GL_VERTEX_SHADER, detail::ShaderType::Vertex);

        glCompileShader(fragmentShader);
        glCompileShader(vertexShader);

        glAttachShader(p_sd.programID, fragmentShader);
        glAttachShader(p_sd.programID, vertexShader);

        //glBindAttribLocation(p_sd.programID, vertexPosIndex, "vPosition");
        //glBindAttribLocation(p_sd.programID, textureCoordIndex, "vTexCoord");

		_bindAttributes(p_sd.programID, p_sd.numAttribs, "a_position");
		_bindAttributes(p_sd.programID, ++p_sd.numAttribs, "a_color");
		_bindAttributes(p_sd.programID, ++p_sd.numAttribs, "a_texCoordinate");


        glLinkProgram(p_sd.programID);

        GLint isLinked = 0;

        glGetProgramiv(p_sd.programID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            //TODO: Android problem //Messenger::Add(Messenger::MessageType::Error, "Failed to link program, shader creation failed ");

            glDeleteProgram(p_sd.programID);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return;
        }

        //Store IDs for later deletion
        p_sd.fragmentShaderID = vertexShader;
        p_sd.vertexShaderID = fragmentShader;
    }
    //////////////////////////////////////////

	void ShaderSystem::_bindAttributes(GLuint p_program, const unsigned int p_numAttributes, const std::string& p_attributeName)
	{
		glBindAttribLocation(p_program, p_numAttributes, p_attributeName.c_str());
	}
	//////////////////////////////////////////



    GLuint ShaderSystem::_loadShader(const std::string& p_shaderDataSource, const GLenum p_type, const detail::ShaderType p_shaderType)
    {
        GLuint shader = 0u;
        GLint success = 0;

        if (!(shader = glCreateShader(p_type)))
        {
            //TODO: Android problems
#ifdef _WIN32
            Messenger::Add(Messenger::MessageType::Error, "Failed to create shader: ", p_shaderDataSource);
#endif
        }
        //const std::string shaderData = _readFile(p_shaderType, p_shaderDataSource).c_str();
        std::string shaderData;
        if(p_shaderType == detail::ShaderType::Fragment)
        {
            shaderData = "#version 110\n"
                    "\n"
                    "precision mediump float;\n"
                    "uniform sampler2D texture;\n"
                    "varying vec2 texCoord;\n"
                    "void main()\n"
                    "{\n"
                    "gl_FragColor = texture2D(texture, texCoord);\n"
                    "}";
        }
        if(p_shaderType == detail::ShaderType::Vertex)
        {
            shaderData = "#version 110\n"
                    "\n"
                    "attribute vec4 vPosition;\n"
                    "attribute vec2 vTexCoord;\n"
                    "varying vec2 texCoord;\n"
                    "void main()\n"
                    "{\n"
                    "\tgl_Position = vPosition;\n"
                    "\ttexCoord = vTexCoord;\n"
                    "}";
        }

        //std::string test = "precision mediump float; void main() {gl_FragColor = vec4(0.f, 1.f, 0.f, 0.5f); }";

        const char* shaderData2 = shaderData.c_str();

        glShaderSource(shader, 1, &shaderData2, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);

            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(shader);

            //TODO: Android problem
            //Messenger::Add(Messenger::MessageType::Error, "Compile shaders failed " + shader);
            return 0u;
        }

        return shader;
    }
    //////////////////////////////////////////


    bool ShaderSystem::_parseShader(const detail::ShaderType p_type, std::string& p_shaderName)
    {
        std::string path = "Shaders/";

        if (!p_shaderName.empty())
        {
            p_shaderName = path + p_shaderName;
            return true;
        }
        else
        {
            switch (p_type)
            {
            case detail::ShaderType::Fragment:
                p_shaderName = path + settings::defaultFragmentShaderFileName;
                return true;

            case detail::ShaderType::Vertex:
                p_shaderName = path + settings::defaultVertexShaderFileName;
                return true;
                
            default:
                return false;
            }
        }
    }
    //////////////////////////////////////////

    std::string ShaderSystem::_readFile(const detail::ShaderType p_type, std::string p_filePath)
    {
        //TODO: Android major fix needed, not able to read shaders currently
#ifdef _WIN32
        FileHandler handler;
#elif defined __ANDROID__
        FileHandler handler(AndroidAppState::m_AppState);
#endif
        if (!handler.Read(p_filePath))
        {
            //Messenger::Add(Messenger::MessageType::Error, "Failed to open shader file ", p_filePath);
            std::string empty = "";
            if (_parseShader(p_type, empty))
            {
                if (!handler.Read(p_filePath))
                {
                   // Messenger::Add(Messenger::MessageType::Error, "Failed to open default shader file ", p_filePath);
                    return "";
                }
            }
            else
            {
                //Messenger::Add(Messenger::MessageType::Error, "Failed to parse default shader file ");
                return "";
            }
        }

        return std::string(handler.m_fileContents.begin(), handler.m_fileContents.end());

        std::string dummyValueForAndroid = "";
        return dummyValueForAndroid;
    }
    //////////////////////////////////////////

    void Use(const GLuint& p_program)
    {
        glUseProgram(p_program);
    }
    //////////////////////////////////////////

    void Unuse(const GLuint& p_program)
    {
        glUseProgram(p_program);
    }
    //////////////////////////////////////////

    void ShaderSystem::_update(const float p_deltaTime)
    {
    }
    //////////////////////////////////////////

}