workspace "bumfer"
    configurations { "Debug", "Release" }
    startproject "bumfer"

project "bumfer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files
    { 
        "src/**.h",
        "src/**.cpp",
        "src/widgets/**.h",
        "src/widgets/**.cpp"
    }

    links
    {
        "GLAD",
        "GLFW",
        "DearImGui"
    }

    includedirs
    {
        "src",
        "thirdparty/glad/include",
        "thirdparty/glfw/include",
        "thirdparty/imgui",
        "thirdparty/imgui/examples"
    }

    filter { "system:Linux" }
        links { "dl", "pthread" }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

include "thirdparty/glad.lua"
include "thirdparty/glfw.lua"
include "thirdparty/imgui.lua"