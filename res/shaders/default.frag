#version 330 core
out vec4 o_FragColor;

in vec2 TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
  o_FragColor = mix(
      texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), 0.2);
}
