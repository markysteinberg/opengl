#include <cstddef>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>

#include <glm/glm.hpp> 

#include "shader.h" 
#include "log.h" 

std::string loadFile(const char* path) {
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const char* vspath, const char* fspath) { 
    std::string vss = loadFile(vspath);
    std::string fss = loadFile(fspath);
    
    if (vss.empty() || fss.empty()) {
        LOG(ERROR, "GLSL shader file failed to load");
        throw std::runtime_error("Failed to load shader file");
    }

    const char* vertex_shader_source = vss.c_str();
    const char* fragment_shader_source =  fss.c_str();

    GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vs_id);
    check_compile(vs_id);

    GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fs_id);
    check_compile(fs_id);

    id = glCreateProgram();
    glAttachShader(id, vs_id);
    glAttachShader(id, fs_id);
    glLinkProgram(id);
    check_link(id);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

void Shader::use() const { glUseProgram(id); }

GLuint Shader::getID() const { return id; }

Shader::~Shader() {
    LOG(INFO, "Deleting shader program ID=", id);
    glDeleteProgram(id);
}
 
void Shader::check_compile(GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG(ERROR, "Shader compilation failed: ", infoLog);
    } else {
        LOG(INFO, "Shader compiled");
    }
}

void Shader::check_link(GLuint program) {
    int success;
    char infoLog[512]; 
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG(ERROR, "Shader program link failed: ", infoLog);
    } else {
        LOG(INFO, "Program linked: ID=", program);
    }
}


void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}