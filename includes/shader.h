#ifndef SHADER_H
#define SHADER_H 

#include <string> 

#include "glad/glad.h" 

#include <glm/glm.hpp>

std::string loadFile(const char* path);

class Shader { 
private: 
    GLuint id;

public:     
    GLint mvpLoc;
    GLint timeLoc;
    GLint hasTexLoc;
    GLint diffuseLoc;
    GLint texLoc;

    void cacheUniforms() {
        mvpLoc = glGetUniformLocation(id, "MVP");
        timeLoc = glGetUniformLocation(id, "time");
        hasTexLoc = glGetUniformLocation(id, "hasTexture");
        diffuseLoc = glGetUniformLocation(id, "diffuse");
        texLoc = glGetUniformLocation(id, "diffuseTex");    
    }

    Shader(const char* vertex_shader_source, const char* fragment_shader_source);
    ~Shader();

    void use() const;
    GLuint getID() const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private: 
    void check_compile(GLuint shader);
    void check_link(GLuint program);
};

#endif 
