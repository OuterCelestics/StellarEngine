#pragma once
#include <glad/glad.h>


class Texture
{
public:
	void TextureInit();
	void Bind();
	unsigned int textureID;
	
	// Image properties
	int width, height, nrChannels;
};

