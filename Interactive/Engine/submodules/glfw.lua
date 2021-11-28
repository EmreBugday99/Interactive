project "GLFW"
    kind "StaticLib"
    language "C"
    architecture "x64"

    targetdir ("binaries/" .. outputdirectory .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdirectory .. "/%{prj.name}")

    includedirs { "glfw/include/" }

    files 
    {
        "glfw/src/glfw_config.h",
        "glfw/src/context.c",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/monitor.c",
        "glfw/src/vulkan.c",
        "glfw/src/window.c"
    }

    filter "system:windows"
        buildoptions {"-std=c11", "-lgdi32"}
        systemversion "latest"
        staticruntime "On"

        files
        {
            "glfw/src/win32_init.c",
            "glfw/src/win32_joystick.c",
            "glfw/src/win32_monitor.c",
            "glfw/src/win32_time.c",
            "glfw/src/win32_thread.c",
            "glfw/src/win32_window.c",
            "glfw/src/wgl_context.c",
            "glfw/src/egl_context.c",
            "glfw/src/osmesa_context_c",
        }

    filter "system:linux"
        pic "On"
        systemversion "latest"
        staticruntime "On"