project "Engine"
	kind "ConsoleApp"
	language "C++"

	targetdir ("../binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("../intermediate/" .. outputdirectory .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
		"src/**.c",
	}

	includedirs
	{
		"libraries/include",
		"dependencies/glfw/include",
		"dependencies/glad/include"
	}

	libdirs {"libraries/libs/"}

	links {"GLFW","Glad","opengl32.lib"}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines "OS_WINDOWS"

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TURTLE_RELEASE"
		optimize "On"