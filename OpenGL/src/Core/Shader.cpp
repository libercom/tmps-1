#include "Shader.h"
#include <GL/glew.h>

#include "../Utils/FileReader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    FileReader fileReader;

    std::string vertexShaderContent = fileReader.ReadFile("./src/Shaders/vertex/vertex.glsl");
    std::string fragmentShaderContent = fileReader.ReadFile("./src/Shaders/fragment/fragment.glsl");

    const char* vertexShaderSource = vertexShaderContent.c_str();
    const char* fragmentShaderSource = fragmentShaderContent.c_str();

    uint32_t vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    uint32_t fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    this->m_ProgramId = glCreateProgram();

    glAttachShader(m_ProgramId, vertexShader);
    glAttachShader(m_ProgramId, fragmentShader);

    glLinkProgram(m_ProgramId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramId);
}

void Shader::Bind()
{
	glUseProgram(m_ProgramId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_ProgramId, name.c_str()), value);
}

void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
{
    glUniform2f(glGetUniformLocation(m_ProgramId, name.c_str()), value.x, value.y);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(glGetUniformLocation(m_ProgramId, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(glGetUniformLocation(m_ProgramId, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
