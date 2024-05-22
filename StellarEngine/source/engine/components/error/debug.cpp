#include <Windows.h>
#include <fstream>
#include <chrono>
#include "debug.h"

void Debug::ErrorLog(const std::string& msg, bool save)
{
	MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);

	if (save)
	{
		std::ofstream file("error.log", std::ios::app);
		file << msg << std::endl;
		file.close();
	}
}
