#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{    
	vec4 c = texture(texture_diffuse1, TexCoords);
	c.r = c.r + 0.1;
	c.g = c.g + 0.1;
	c.b = c.b + 0.1;
    color = vec4(c);
}
