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
#ifdef _WIN32
        if (!_parseShader(detail::ShaderType::Fragment, p_sd.fragmentShaderFileName))
            Messenger::Add(Messenger::MessageType::Error, "Failed to parse fragment shader ");

        if (!_parseShader(detail::ShaderType::Vertex, p_sd.vertexShaderFileName))
            Messenger::Add(Messenger::MessageType::Error, "Failed to parse vertex shader ");
#endif
        if (!(p_sd.programID = glCreateProgram()))
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to create GL program");
            return;
        }

        GLuint vertexShader = _loadShader((p_sd.vertexShaderFileName), GL_VERTEX_SHADER, detail::ShaderType::Vertex);
        GLuint fragmentShader = _loadShader((p_sd.fragmentShaderFileName), GL_FRAGMENT_SHADER, detail::ShaderType::Fragment);

        glCompileShader(fragmentShader);
        glCompileShader(vertexShader);

        glAttachShader(p_sd.programID, fragmentShader);
        glAttachShader(p_sd.programID, vertexShader);

        //glBindAttribLocation(p_sd.programID, vertexPosIndex, "vPosition");
        //glBindAttribLocation(p_sd.programID, textureCoordIndex, "vTexCoord");

        _bindAttributes(p_sd.programID, ++p_sd.numAttribs, "a_position");
        _bindAttributes(p_sd.programID, ++p_sd.numAttribs, "a_texCoordinate");
        _bindAttributes(p_sd.programID, ++p_sd.numAttribs, "a_color");


        glLinkProgram(p_sd.programID);

        GLint isLinked = 0;

        glGetProgramiv(p_sd.programID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to link program, shader creation failed ");

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
            Messenger::Add(Messenger::MessageType::Error, "Failed to create shader: ", p_shaderDataSource);


        const std::string shaderData = _readFile(p_shaderType, p_shaderDataSource).c_str();

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

            Messenger::Add(Messenger::MessageType::Error, "Compile shaders failed " + shader);
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
                p_shaderName = path + settings::Settings::defaultFragmentShaderFileName;
                return true;

            case detail::ShaderType::Vertex:
                p_shaderName = path + settings::Settings::defaultVertexShaderFileName;
                return true;

            default:
                return false;
            }
        }
    }
    //////////////////////////////////////////

    std::string ShaderSystem::_readFile(const detail::ShaderType p_type, std::string p_filePath)
    {
        
        FileHandler handler;

        if (!handler.Read(p_filePath))
        {
            Messenger::Add(Messenger::MessageType::Error, "Failed to open shader file ", p_filePath);
            std::string empty = "";
            if (_parseShader(p_type, empty))
            {
                if (!handler.Read(p_filePath))
                {
                    Messenger::Add(Messenger::MessageType::Error, "Failed to open default shader file ", p_filePath);
                    return "";
                }
            }
            else
            {
                Messenger::Add(Messenger::MessageType::Error, "Failed to parse default shader file ");
                return "";
            }
        }

        const auto& data = handler.GetReadDataRef();
        return std::string(data.begin(), data.end());



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

    bool ShaderSystem::_finalize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////

    bool ShaderSystem::_initialize()
    {
        //TODO:
        return true;
    }
    //////////////////////////////////////////
}