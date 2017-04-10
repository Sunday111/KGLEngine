// Simplest fragment shader
#version 330 core

out vec4 color;
uniform vec3 gu_color;

void main()
{
    color = vec4(gu_color, 1.0f);
}