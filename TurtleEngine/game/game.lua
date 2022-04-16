project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

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
        "../turtle-core/src",
		"../dependencies/glad/include",
		"../dependencies/glm",
		"../dependencies/box2d"
	}

	links {"TurtleCore"}

	-- Defines without any filter
	defines {"TURTLE_GAME"}

	filter "system:windows"
		defines {"TURTLE_OS_WINDOWS", "TURTLE_GAME"}

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "TURTLE_RELEASE"
		optimize "on"