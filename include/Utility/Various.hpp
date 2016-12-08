#ifndef JEJ_VARIOUS_HPP
#define JEJ_VARIOUS_HPP

#include <External/OpenGL_ES2/EGL/egl.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>

#include <string>

namespace jej
{
    namespace various
    {

        //Temp for testing or other small stuff here



        void j_glError()
        {
            std::string eMsg = "";
            auto error = glGetError();

            while (error != GL_NO_ERROR)
            {
                switch (error)
                {
                case GL_INVALID_ENUM: eMsg = "GL invalid enum"; break;
                case GL_INVALID_VALUE: eMsg = "GL invalid value"; break;
                case GL_INVALID_OPERATION: eMsg = "GL invalid operation"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: eMsg = "GL invalid framebuffer operation"; break;
                case GL_OUT_OF_MEMORY: eMsg = "GL out of memory"; break;
                default: break;
                }

                if (!eMsg.empty())
                    Messenger::Add(Messenger::MessageType::Error, eMsg);

                error = glGetError();
            }

        }



    }
}
#endif