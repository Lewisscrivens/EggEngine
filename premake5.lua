workspace "EggEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Development"
	}
	
winbinariesdir = "EggEngine/Binaries/Win64/"
winintermediatedir = "EggEngine/Intermediate/Win64/"
	
project "EggEngine"
	location "EggEngine/Source/Runtime"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir (winbinariesdir .. "/%{prj.name}")
	objdir (winintermediatedir .. "/%{prj.name}")
	
	pchheader "EggPch.h"
	pchsource "EggEngine/Source/Runtime/EggPch.cpp"

	files
	{
		"EggEngine/Source/Runtime/**.h",
		"EggEngine/Source/Runtime/**.cpp"
	}
	
	includedirs
	{
		"EggEngine/Source/Runtime",
		"EggEngine/Source/ThirdParty/Spdlog/include",
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS",
			"EGG_BUILD",
			"_CRT_SECURE_NO_WARNINGS"
		}

		postbuildcommands
		{
			
		}
		
	filter "configurations:Debug"
		defines "EGG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Development"
		defines "EGG_DEV"
		runtime "Release"
		optimize "on"
		
project "EggEditor"
	location "EggEngine/Source/Programs/Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir (winbinariesdir .. "/%{prj.name}")
	objdir (winintermediatedir .. "/%{prj.name}")
	
	files
	{
		"EggEngine/Source/Programs/Editor/**.h",
		"EggEngine/Source/Programs/Editor/**.cpp"
	}
	
	includedirs
	{
		"EggEngine/Source/Runtime",
		"EggEngine/Source/ThirdParty/Spdlog/include"		
	}
	
	links
	{
		"EggEngine"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "EGG_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Development"
		defines "EGG_DEV"
		runtime "Release"
		optimize "on"