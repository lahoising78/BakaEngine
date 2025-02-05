#include <string>

#include "GL/glew.h"

#include "baka_logger.h"
#include "baka_gl/utils.h"

#include "baka_gl/shaders.h"

namespace baka
{
    namespace gl
    {
        Shader::Shader(const char *vertSrc, const char *fragSrc)
        {
            BAKA_ASSERT(vertSrc);
            BAKA_ASSERT(fragSrc);

            unsigned int renderer_program_id = glCreateProgram();
            unsigned int vert = this->CompileShader(GL_VERTEX_SHADER, vertSrc);
            unsigned int frag = this->CompileShader(GL_FRAGMENT_SHADER, fragSrc);

            GLCALL(glAttachShader(renderer_program_id, vert));
            GLCALL(glAttachShader(renderer_program_id, frag));
            GLCALL(glLinkProgram(renderer_program_id));
            GLCALL(glValidateProgram(renderer_program_id));
            
            GLCALL(glDeleteShader(vert));
            GLCALL(glDeleteShader(frag));

            this->renderer_program_id = renderer_program_id;
        }

        void Shader::Destroy()
        {
            glDeleteProgram(this->renderer_program_id);
        }

        unsigned int Shader::CompileShader(unsigned int shaderType, const char *source)
        {
            BAKA_ASSERT(source);

            unsigned int id = glCreateShader(shaderType);
            GLCALL(glShaderSource(id, 1, &source, nullptr));
            GLCALL(glCompileShader(id));

            int result;
            GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
            if(result != GL_FALSE) return id;

            int length;
            GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            std::string msg;
            msg.resize(length);
            GLCALL(glGetShaderInfoLog(id, length, &length, (char *)(&msg[0])));

            bakalog("Failed to compile %s shader", shaderType == GL_VERTEX_SHADER? "vertex" : "fragment");
            bakalog("%s", msg.c_str());

            return 0;
        }

        void Shader::Bind()
        {
            glUseProgram(this->renderer_program_id);
        }
    }
} // namespace baka
