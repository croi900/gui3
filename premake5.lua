workspace "gui3"
    configurations { "Debug", "Release" }

project "gui3"
    location "build"
    kind "ConsoleApp"
    language "C++"

    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }
    libdirs{ "lib" }
    includedirs { "include" }
    links { "raylib", "opengl32","gdi32", "winmm"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
      --  architecture "x86_64"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
      --  architecture "x86_64"