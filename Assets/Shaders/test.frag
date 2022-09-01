#version 410 core
in vec4 pos;
out vec4 out_color;

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void main()
{
    out_color = vec4(pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f, 1.0f);
}
