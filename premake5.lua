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
	kind "SharedLib"
	language "C++"
	
	targetdir (winbinariesdir .. "/%{prj.name}")
	objdir (winintermediatedir .. "/%{prj.name}")

	files
	{
		"EggEngine/Source/Runtime/**.h",
		"EggEngine/Source/Runtime/**.cpp"
	}
	
	includedirs
	{
		"EggEngine/Source/ThirdParty/Spdlog/include",
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"
		
		defines
		{
			"PLATFORM_WINDOWS",
			"EGG_BUILD"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} %{cfg.buildtarget.directory}../EggEditor/" )
		}
		
	filter "configurations:Debug"
		defines "EGG_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "EGG_DEV"
		optimize "On"
		
project "EggEditor"
	location "EggEngine/Source/Programs/Editor"
	kind "ConsoleApp"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"
		
		defines
		{
			"PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "EGG_DEBUG"
		symbols "On"
		
	filter "configurations:Development"
		defines "EGG_DEV"
		optimize "On"