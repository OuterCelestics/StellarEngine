-- premake5.lua
workspace "StellarEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Application"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
   include "Submodules/GLFW/Build-Windows.lua"

group "Engine"
	include "Engine/Build-Engine.lua"
group ""

include "Application/Build-Application.lua"