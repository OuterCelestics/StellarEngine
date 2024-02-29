#include "context.h"

void Context::initialize()
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = GetModuleHandle(0);
	wc.lpszClassName = L"Stellar Client Application | ShaderCompileWorker";
	RegisterClass(&wc);

	m_hwnd = CreateWindow(wc.lpszClassName, L"Stellar Client Application | ShaderCompileWorker", 0, 0, 0, 1, 1, 0, 0, GetModuleHandle(0), 0);
	m_hdc = GetDC(m_hwnd);

	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0};

	int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, pixelFormat, &pfd);

	m_hglrc = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_hglrc);
}
