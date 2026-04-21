#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D diffuseTex;
uniform vec3 diffuse;
uniform bool hasTexture;
uniform float time;

void main() {
   vec3 color = hasTexture ? texture(diffuseTex, TexCoord).rgb : diffuse;
   FragColor = vec4(color, 1.0);
}
