#include "textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <filesystem>

void Texture::TextureInit()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set the filtering params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Flip the texture because it was flipped for some reason
	stbi_set_flip_vertically_on_load(true);

	// Load the texture using stb_load
	unsigned char* data = stbi_load("textures/cat.png", &width, &height, &nrChannels, 0);
	
	// Check if the texure is laoded properly ( Check if data contains some stuff)
	if (data != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture %s", data);
	}

	// Free the image data from stbi because we have loaded it with `glTexImage2D`
	stbi_image_free(data);
}

void Texture::Bind() 
{
	glActiveTexture(GL_TEXTURE0);
	//std::cout << textureID << std::endl; // Print ID for debugging purposes
	glBindTexture(GL_TEXTURE_2D, textureID);
}