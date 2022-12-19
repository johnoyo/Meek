project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("IMGUI/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("IMGUI/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"IMGUI/imconfig.h",
		"IMGUI/imgui.h",
		"IMGUI/imgui.cpp",
		"IMGUI/imgui_draw.cpp",
		"IMGUI/imgui_internal.h",
		"IMGUI/imgui_tables.cpp",
		"IMGUI/imgui_widgets.cpp",
		"IMGUI/imstb_rectpack.h",
		"IMGUI/imstb_textedit.h",
		"IMGUI/imstb_truetype.h",
		"IMGUI/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"