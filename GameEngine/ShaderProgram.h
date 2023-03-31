#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <unordered_map>
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    ~ShaderProgram();

    GLuint getProgram() const;

    void bind() const;
    void unbind() const;

    void setUniformInt(const std::string& name, int value);
    void setUniformFloat(const std::string& name, float value);
    void setUniformVec3(const std::string& name, const glm::vec3& value);
    void setUniformMat4(const std::string& name, const glm::mat4& value);

private:
    GLuint m_program;
    std::unordered_map<std::string, GLint> m_uniforms;

    GLint getUniformLocation(const std::string& name);
};

#endif // !SHADER_PROGRAM_H

