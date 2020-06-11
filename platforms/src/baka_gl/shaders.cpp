#include <string>

#include "GL/glew.h"

#include "baka_logger.h"
#include "baka_gl/shaders.h"

namespace baka
{
    namespace gl
    {
        unsigned int Shader::Create(const char *vertSource, const char *fragSource)
        {
            BAKA_ASSERT(vertSource);
            BAKA_ASSERT(fragSource);

            unsigned int renderer_program_id = glCreateProgram();
            unsigned int vert = this->CompileShader(GL_VERTEX_SHADER, vertSource);
            unsigned int frag = this->CompileShader(GL_FRAGMENT_SHADER, fragSource);

            glAttachShader(renderer_program_id, vert);
            glAttachShader(renderer_program_id, frag);
            glLinkProgram(renderer_program_id);
            glValidateProgram(renderer_program_id);

            glDeleteShader(vert);
            glDeleteShader(frag);

            this->renderer_program_id = renderer_program_id;
            return renderer_program_id;
        }

        void Shader::Destroy()
        {
            glDeleteProgram(this->renderer_program_id);
        }

        unsigned int Shader::CompileShader(unsigned int shaderType, const char *source)
        {
            BAKA_ASSERT(source);

            unsigned int id = glCreateShader(shaderType);
            glShaderSource(id, 1, &source, nullptr);
            glCompileShader(id);

            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if(result != GL_FALSE) return id;

            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::string msg;
            msg.resize(length);
            glGetShaderInfoLog(id, length, &length, (char *)(&msg[0]));

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
