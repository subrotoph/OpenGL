#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 vColor;
out vec2 vTexCoord;

void main() {
    vColor = color;
    vTexCoord = texCoord;
    gl_Position = vec4(position, 1.0);
}
