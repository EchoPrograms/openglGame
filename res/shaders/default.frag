#version 330 core
out vec4 o_FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{
  // Simple ambient lighting
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  vec3 objectColor = vec3(0.5, 0.5, 0.8);
  
  float ambientStrength = 0.3;
  vec3 ambient = ambientStrength * lightColor;
  
  // Simple diffuse lighting
  vec3 lightPos = vec3(5.0, 5.0, 5.0);
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  
  vec3 result = (ambient + diffuse) * objectColor;
  o_FragColor = vec4(result, 1.0);
}
