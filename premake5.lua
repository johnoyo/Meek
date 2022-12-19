workspace "MeekApp"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "MeekApp"

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

group "Dependencies"
    include "ThirdParty/IMGUI"
    include "ThirdParty/GLFW"
group ""

group "Core"
    project "Meek"
        location "Meek"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "off"

        files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

        includedirs
        {
            "Meek/src",
            "ThirdParty/IMGUI/IMGUI",
            "ThirdParty/IMGUI/IMGUI/backends",
            "ThirdParty/GLFW/GLFW/include",
            "ThirdParty/GLEW/include",
            "ThirdParty/stb_image",
            "ThirdParty/GLM"
        }
    
        libdirs
        {
            "ThirdParty/GLEW/lib/Release/x64"
        }
    
        links
        {
            "opengl32.lib",
            "glew32s.lib",
            "ImGui",
            "GLFW"
        }

        defines 
        {
            "GLEW_STATIC"
        }

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        filter "system:windows"
            systemversion "latest"
            defines { "M_PLATFORM_WINDOWS" }

        filter "configurations:Debug"
            defines { "M_DEBUG" }
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines { "M_RELEASE" }
            runtime "Release"
            optimize "On"
            symbols "On"

        filter "configurations:Dist"
            defines { "M_DIST" }
            runtime "Release"
            optimize "On"
            symbols "Off"
group ""

project "MeekApp"
    location "MeekApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs
    {
        "ThirdParty/IMGUI/IMGUI",
        "ThirdParty/IMGUI/IMGUI/backends",
        "ThirdParty/GLFW/GLFW/include",
        "ThirdParty/GLEW/include",
        "ThirdParty/GLM",
        "ThirdParty/stb_image",
        "Meek/src"
    }

    links
    {
        "Meek"
    }

    defines 
    {
        "GLEW_STATIC"
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "M_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "M_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "M_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "M_DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
