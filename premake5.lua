workspace "EggEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-${cfg.architecture}"
	
project "EggEngine"
	location "EggEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}
	
	includedirs
	{
		"EggEngine/Source",
		
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"
		
		defines
		{
			"PLATFORM_WINDOWS",
			"EGG_BUILD",
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/EggEditor")
		}

	filter "configurations:Debug"
		defines "EGG_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EGG_RELEASE"
		optimize "On"
		
project "EggEditor"
	location "EggEditor"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}
	
	includedirs
	{
		"EggEngine/Source",
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
			"PLATFORM_WINDOWS",
		}
		
	filter "configurations:Debug"
		defines "EGG_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EGG_RELEASE"
		optimize "On"