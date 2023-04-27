#version 410 core
layout (location = 0) in vec4 in_pos;
layout (location = 1) in vec4 in_color;
out vec4 pos;
out vec4 color;

void main()
{
    gl_Position = vec4(in_pos.x, in_pos.y, in_pos.z, 1.0);
    color = in_color;
    pos = gl_Position;
}
