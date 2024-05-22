#pragma once
#include <string>
#include "../../core.h"

class ENGINE_API Debug {
public:
	static void ErrorLog(const std::string& msg, bool save);
};
