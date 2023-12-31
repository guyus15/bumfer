project "GLAD"
    kind "StaticLib"
    language "C"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"

    includedirs { "glad/include" }

    files { "glad/src/glad.c" }

    filter { "system:Linux" }
        pic "On"
        systemversion "latest"
        staticruntime "On"

        defines { "_GLAD_X11" }

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        runtime "Release"
        optimize "On"