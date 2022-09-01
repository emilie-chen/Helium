#version 410 core
layout (location = 0) in vec4 in_pos;
out vec4 pos;

void main()
{
    gl_Position = vec4(in_pos.x, in_pos.y, in_pos.z, 1.0);
    pos = gl_Position;
}
