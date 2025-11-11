#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;
out vec3 vertColor;
out vec2 TexCoord;
void main()
{
 gl_Position = vec4(a_Pos, 1.0);
 vertColor = a_Color;
 TexCoord = a_TexCoord;
}
