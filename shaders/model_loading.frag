#version 330 core

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;

out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{    
	vec4 c = texture(texture_diffuse1, TexCoords);

    color = c;
}
