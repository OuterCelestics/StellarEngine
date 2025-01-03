#version 460 core
out vec4 FragColor;

in vec2 TextCoord;

// Texture sampler
uniform layout(location = 0) sampler2D texture1;

void main() {
    // Make the color orange
    FragColor = vec4(1.5, 1.0, 1.5, 1.5) * texture(texture1, TextCoord);
}
