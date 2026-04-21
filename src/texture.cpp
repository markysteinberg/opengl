#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"
#include "log.h"

GLuint load_texture(const char* path) {
    int width = 0, height = 0, channels = 0;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        LOG(ERROR, "Texture load failed: ", path);
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    LOG(INFO, "Textured loaded: ", path, " w=", width, " h=", height, " channels=", channels, " format=", (format == GL_RGBA ? "GL_RGBA" : "GL_RGB"));

    GLuint tex; 
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    LOG(INFO, "Texture ID: ", tex);
    return tex;
}
