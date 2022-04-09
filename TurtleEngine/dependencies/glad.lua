project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("../binaries/" .. outputdirectory .. "/%{prj.name}")
    objdir ("../intermediate/" .. outputdirectory .. "/%{prj.name}")

    files 
    {
        "glad/include/glad/glad.h",
        "glad/include/KHR/khrplatform.h",
        "glad/src/glad.c",
    }

    includedirs {"glad/include"}

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"
        files
        {
            "glad/include/glad/glad_wgl.h",
            "glad/src/glad_wgl.c"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"