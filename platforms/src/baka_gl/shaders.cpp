#include <string>

#include "GL/glew.h"

#include "baka_logger.h"
#include "baka_gl/shaders.h"

namespace baka
{
    unsigned int GLShader::Create(const char *vertSource, const char *fragSource)
    {
        unsigned int program = glCreateProgram();
        unsigned int vert = this->CompileShader(GL_VERTEX_SHADER, vertSource);
        unsigned int frag = this->CompileShader(GL_FRAGMENT_SHADER, fragSource);

        glAttachShader(program, vert);
        glAttachShader(program, frag);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vert);
        glDeleteShader(frag);

        this->program = program;
        return program;
    }

    void GLShader::Destroy()
    {
        glDeleteProgram(this->program);
    }

    unsigned int GLShader::CompileShader(unsigned int shaderType, const char *source)
    {
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

    void GLShader::Bind()
    {
        glUseProgram(this->program);
    }
} // namespace baka
