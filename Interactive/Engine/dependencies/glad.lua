project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("../../binaries/" .. outputdirectory .. "/%{prj.name}")
    objdir ("../../intermediate/" .. outputdirectory .. "/%{prj.name}")

    includedirs {"glad/include/"}

    files
    {
        "glad/include/KHR/khrplatform.h",
        "glad/include/glad/glad.h",
        "glad/src/glad.c"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"