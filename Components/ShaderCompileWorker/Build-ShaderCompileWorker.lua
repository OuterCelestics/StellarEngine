project "ShaderCompileWorker"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"
    
    files {
        "source/**.h",
        "source/**.cpp",
        "source/**.c"
     }
    
    includedirs{
        "$(SolutionDir)Dependencies/Glad/include"
    }

    sysincludedirs {
        "$(SolutionDir)Dependencies/include"
    }

    links {
       "opengl32",
    }
   
    targetdir ("../Binaries/" .. OutputDir .. "/")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/")