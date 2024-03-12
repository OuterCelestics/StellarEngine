#version 460 core
out vec4 FragColor;

in vec4 TextCoord;

// Texture sampler
uniform sampler2D texture1;

void main()
{
    FragColor = vec4(texture1, TextCoord);
}