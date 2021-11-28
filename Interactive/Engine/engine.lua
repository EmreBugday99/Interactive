project "Engine"
	kind "ConsoleApp"
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
		"dependencies/stb/stb_image.h",
		"dependencies/glad/src/glad.c"
	}

	includedirs
	{
		"dependencies/glfw/include",
		"dependencies/glad/include",
		"dependencies/glm"
	}

	libdirs {"dependencies/glfw/lib-vc2019"}
	links {"glfw3.lib", "opengl32.lib"}

	filter "system:windows"
		systemversion "latest"
		defines "TURTLE_OS_WINDOWS"

	filter "configurations:Debug"
		defines "TURTLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "TURTLE_RELEASE"
		optimize "on"