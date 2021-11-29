project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

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
		"dependencies/glfw/include",
		"dependencies/glad/include",
		"dependencies/glm"
	}

	links {"GLFW", "Glad","opengl32.lib"}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines {"TURTLE_OS_WINDOWS", "GLFW_INCLUDE_NONE"}

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "TURTLE_RELEASE"
		optimize "on"