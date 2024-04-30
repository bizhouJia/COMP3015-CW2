#version 460

// Input light intensity from vertex shader
in vec3 LightIntensity;

uniform int Pass;

// Output fragment color
layout (location = 0) out vec4 FragColor;

vec4 pass()
{
    return vec4(LightIntensity, 1.0);
}

void main() {
    FragColor = pass();
}
