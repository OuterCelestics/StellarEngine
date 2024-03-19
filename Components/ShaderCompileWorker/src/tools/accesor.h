#pragma once

#include <Windows.h>
#include <iostream>

class Accesor {
public:
	int buffer_size = 1024;

	HANDLE hMapFile;
	LPCTSTR pBuf;

	bool initialize();
	void write(const char* data, int delay);
};
