#ifndef SHADER_H
#define SHADER_H 

#include <string> 

using GLuint = unsigned int;

std::string loadFile(const char* path);

class Shader { 
private: 
    GLuint id;

public:     
    Shader(const char* vertex_shader_source, const char* fragment_shader_source);

    void use() const;

    GLuint getID() const;

    ~Shader();

    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const;

private: 
    void check_compile(GLuint shader);
    void check_link(GLuint program);
};

#endif 