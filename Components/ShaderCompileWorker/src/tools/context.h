#pragma once

#include <Windows.h>

class Context {
public:
	void initialize();
public:
	HWND m_hwnd;
	HDC m_hdc;
	HGLRC m_hglrc;
};