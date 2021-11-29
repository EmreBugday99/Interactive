project "TurtleCore"
	kind "SharedLib"
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
		"dependencies/glad/include",
		"dependencies/glm"
	}

	links {"Glad","opengl32.lib"}

	-- Defines without any filter
	defines {"TURTLE_CORE"}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines {"TURTLE_OS_WINDOWS", "TURTLE_CORE_SHARED"}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../binaries/" .. outputdirectory .. "/Game")
		}

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "TURTLE_RELEASE"
		optimize "on"