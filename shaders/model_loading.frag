#version 330 core

in vec2 TexCoords;
in vec3 Position;

out vec4 color;

uniform sampler2D texture1;

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
}; 

uniform Light light;

void main()
{
  vec3 lightDir = normalize(light.position - Position);

  // Check if lighting is inside the spotlight cone
  float theta = dot(lightDir, normalize(-light.direction)); 
  if(theta > light.cutOff) {
    color = vec4(0.7,0.7,0.7,1.0);
  } else {
    color = texture(texture1, TexCoords);
  }
}
