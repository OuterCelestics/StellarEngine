#pragma once
#include <glad/glad.h>


class Texture
{
public:
	void TextureInit();
	void Bind();
	unsigned int texture;

	//Load the image, create the texure and generate mipmaps
	int width, height, nrChannels;
};

