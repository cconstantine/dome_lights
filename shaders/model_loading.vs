#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec2 texCoordsOffset;
layout (location = 4) in vec3 proj;
layout (location = 5) in mat4 model;

out vec2 TexCoords;
out vec4 Position;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords + texCoordsOffset;
    Position = model * vec4(proj, 1.0f);
}