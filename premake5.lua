workspace "bumfer"
    configurations { "Debug", "Release" }
    startproject "bumfer"

project "bumfer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files { "src/**.h", "src/**.cpp" }

    links { "GLAD", "GLFW" }

    includedirs { "src", "thirdparty/glad/include", "thirdparty/glfw/include" }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

include "thirdparty/glad.lua"
include "thirdparty/glfw.lua"