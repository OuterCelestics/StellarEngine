#include "accesor.h"

bool Accesor::initialize()
{
	std::cout << "buffer_size: " << buffer_size << std::endl;

	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		buffer_size,				     // maximum object size (low-order DWORD)
		L"shader_hot_reload_address"); // name of mapping object

	if (hMapFile == NULL)
	{
		std::cerr << "Could not create file mapping object " << GetLastError() << std::endl;
		return false;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		buffer_size);

	if (pBuf == NULL) {
		std::cerr << "Could not map view of file " << GetLastError() << std::endl;
		CloseHandle(hMapFile);
		return false;
	}
	else {
		std::cout << "Mapped view of file" << std::endl;
		return true;
	}
}

void Accesor::write(const char* data, int delay)
{
	if (CopyMemory((PVOID)pBuf, data, (strlen(data) * sizeof(char)))) {
		std::cout << "Data written to the file mapping object" << std::endl;
	}
	else {
		std::cerr << "Could not write to the file mapping object " << GetLastError() << std::endl;
	}

	Sleep(delay);

	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
}
