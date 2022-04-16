project "Box2D"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"

    targetdir ("../binaries/" .. outputdirectory .. "/%{prj.name}")
    objdir ("../intermediate/" .. outputdirectory .. "/%{prj.name}")

    files 
    {
		"box2d/**.h",
		"box2d/**.hpp",
		"box2d/**.cpp",
		"box2d/**.c",
    }

    includedirs {"box2d/include"}

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"