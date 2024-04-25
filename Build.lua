-- premake5.lua
workspace "Stellar"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "StellarEditor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
   include "Submodules/GLFW/Build-GLFW.lua"

group "Engine"
	include "StellarEngine/Build-StellarEngine.lua"
group ""

include "StellarEditor/Build-StellarEditor.lua"