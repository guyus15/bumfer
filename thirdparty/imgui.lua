project "DearImGui"
    kind "StaticLib"
    language "C"
    
    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"

    includedirs { "imgui", "glad/include", "glfw/include" }

    files
    {
        "imgui/imgui.cpp",
        "imgui/imgui_demo.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.cpp"
    }

    defines { "IMGUI_IMPL_OPENGL_LOADER_GLAD" }

    filter { "system:Linux" }
        pic "On"
        systemversion "latest"
        staticruntime "On"

        defines { "_IMGUI_X11" }

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Debug" }
        runtime "Release"
        optimize "On"
