outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "TurtleEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

project "Engine"
	location "Engine"
	kind "ConsoleApp"
	language "C++"

	targetdir ("binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdirectory .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"%{prj.name}/libraries/include/**"
	}

	libdirs
	{
		"%{prj.name}/libraries/libs/"
	}

	links 
	{
		"opengl32",
		"glfw3"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		defines "OS_WINDOWS"

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TURTLE_RELEASE"
		optimize "On"