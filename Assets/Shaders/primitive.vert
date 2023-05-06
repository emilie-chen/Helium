#version 460 core
layout (location = 0) in vec4 in_pos;
layout (location = 1) in vec4 in_color;

out vec4 color;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    color = in_color;
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * in_pos;
}
