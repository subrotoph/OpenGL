#version 410 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

void main() {
    vec4 worldPos = model * vec4(position, 1.0);
    FragPos = vec3(worldPos);
    TexCoords = texCoords;
    Normal = transpose(inverse(mat3(model))) * normal;

    gl_Position = projection * view * worldPos;
    
}

