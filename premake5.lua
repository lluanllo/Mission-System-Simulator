workspace "Mission_Management_System"
    architecture "x86_64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

    flags {
        "MultiProcessorCompile"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Mission_Management_System"
	location "Mission_Management_System"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/%{outputdir}/%{prj.name}")
	objdir ("bin-int/%{outputdir}/%{prj.name}")


	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
        "%{prj.name}/src/**.inl",
        "%{prj.name}/src/**.py",
        "%{prj.name}/src/**.lua",
	}

	includedirs {
		"%{prj.name}/src",
		"vendor/spdlog/include",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	
    filter "system:windows"
        buildoptions { "/utf-8" }

	filter "configurations:Debug"
		defines { "MMS_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "MMS_RELEASE" }
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines { "MMS_DIST" }
		runtime "Release"
		optimize "On"