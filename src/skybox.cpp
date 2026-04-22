#include <vector> 
#include <string> 

#include <glad/glad.h>
#include <glm/glm.hpp> 

#include "stb_image.h"

#include "skybox.h" 
#include "log.h" 

Skybox::Skybox() : shader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag") {
    setupCube();

    faces = {
        "assets/objects+textures/skybox/right.png",   // +X
        "assets/objects+textures/skybox/left.png",    // -X
        "assets/objects+textures/skybox/top.png",     // +Y
        "assets/objects+textures/skybox/bottom.png",  // -Y
        "assets/objects+textures/skybox/front.png",   // +Z
        "assets/objects+textures/skybox/back.png",    // -Z
    };
    cubeMapTex = loadCubeMap(faces);

    shader.use();
    shader.setInt("skybox", 0);
} 

void Skybox::draw(const glm::mat4 view, const glm::mat4 projection) { 
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    shader.use();

    glm::mat4 viewNoTranslate = glm::mat4(glm::mat3(view));

    shader.setMat4("view", viewNoTranslate);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void Skybox::setupCube() {
    float vertices[] = {
        -1,-1,-1,  1,-1,-1,  1, 1,-1,  1, 1,-1, -1, 1,-1, -1,-1,-1,
        -1,-1, 1,  1,-1, 1,  1, 1, 1,  1, 1, 1, -1, 1, 1, -1,-1, 1,
        -1, 1, 1, -1, 1,-1, -1,-1,-1, -1,-1,-1, -1,-1, 1, -1, 1, 1,
         1, 1, 1,  1, 1,-1,  1,-1,-1,  1,-1,-1,  1,-1, 1,  1, 1, 1,
        -1,-1,-1,  1,-1,-1,  1,-1, 1,  1,-1, 1, -1,-1, 1, -1,-1,-1,
        -1, 1,-1,  1, 1,-1,  1, 1, 1,  1, 1, 1, -1, 1, 1, -1, 1,-1
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
}

GLuint Skybox::loadCubeMap(const std::vector<std::string>& faces) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    stbi_set_flip_vertically_on_load(false);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (faces.size() != 6)  {
        LOG(ERROR, "Cubemap requires 6 faces");
    }

    int w, h, c; 
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &c, 0);
        if (data) {
            GLenum format = (c == 4) ? GL_RGBA : GL_RGB;
            
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            LOG(ERROR, "Failed to load cubemap face: ", faces[i]);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return tex;
}