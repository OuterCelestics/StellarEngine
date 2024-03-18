#version 460 core
out vec4 FragColor;

in vec2 TextCoord;

// Texture sampler
uniform layout(location = 0) sampler2D texture1;

void main() {
    FragColor = texture(texture1, TextCoord);
}