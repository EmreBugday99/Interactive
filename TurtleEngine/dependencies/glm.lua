project "GLM"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"

    targetdir ("../binaries/" .. outputdirectory .. "/%{prj.name}")
    objdir ("../intermediate/" .. outputdirectory .. "/%{prj.name}")

    files 
    {
		"glm/**.h",
		"glm/**.hpp",
		"glm/**.cpp",
		"glm/**.c",
    }

    includedirs {"glm"}

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"