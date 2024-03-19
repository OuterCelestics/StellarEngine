#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <glad/glad.h>

class Accesor {
public:
	int buffer_size = 1024;

	HANDLE hMapFile;
	LPCTSTR pBuf;

	bool initialize();
	void write(std::vector<GLubyte>, int delay);
};
