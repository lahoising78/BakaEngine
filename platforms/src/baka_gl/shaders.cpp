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

        Shader::~Shader()
        {
            this->Destroy();
        }

        void Shader::Destroy()
        {
            bakalog("destroy shader");
            glDeleteProgram(this->renderer_program_id);
            glUseProgram(0);
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

        void Shader::Unbind()
        {
            glUseProgram(0);
        }

        void Shader::SetUniform(UniformType shaderType, const char *name, void *data)
        {
            GLint location = 0;
            if(this->varLocations.find(name) == this->varLocations.end())
            {
                this->varLocations[name] = glGetUniformLocation(this->renderer_program_id, name);
            }
            location = this->varLocations[name];

            switch (shaderType)
            {
            case UniformType::FLOAT:
                glUniform1fv(location, 1, (GLfloat*)data);
                break;

            case UniformType::FLOAT2:
                glUniform2fv(location, 1, (GLfloat*)data);
                break;

            case UniformType::FLOAT3:
                glUniform3fv(location, 1, (GLfloat*)data);
                break;

            case UniformType::FLOAT4:
                glUniform4fv(location, 1, (GLfloat*)data);
                break;

            case UniformType::MAT4X4:
                glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)data);
                break;
            
            default:
                break;
            }
        }
    }
} // namespace baka
