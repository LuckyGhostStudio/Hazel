workspace "Hazel"		--�����������
	architecture "x64"	--��ϵ�ṹ
	startproject "Sandbox"	--Set Start Projrct

	configurations		--����
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	--���Ŀ¼

--����Ŀ¼�б�
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/vendor/GLAD/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"
IncludeDir["stb_image"] = "Hazel/vendor/stb_image"

group "Dependencies"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"

group ""

project "Hazel"	
	location "Hazel"	--���·��
	kind "StaticLib"	--Static Library
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	--Ŀ��Ŀ¼
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	--�м�Ŀ¼

	pchheader "hzpch.h"	--Ԥ����ͷ�ļ�
	pchsource "Hazel/src/hzpch.cpp"

	files				--�ļ�
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs			--���Ӱ���Ŀ¼
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",			--����GLFW
		"GLAD",			--����GLAD
		"ImGui",		--����imgui
		"opengl32.lib"
	}

	filter "system:windows"
        systemversion "latest"	--sdk�汾

		defines			--��
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"	--Debug
        defines "HZ_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"	--Release
        defines "HZ_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"	--Dist
        defines "HZ_DIST"
		runtime "Release"
        optimize "on"

project "Sandbox"
	location "Sandbox"	--���·��
	kind "ConsoleApp"	--����̨Ӧ��
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	--Ŀ��Ŀ¼
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	--�м�Ŀ¼

	files				
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs			--���Ӱ���Ŀ¼
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"Hazel/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hazel"			
	}

	filter "system:windows"	--windows
        systemversion "latest"	--sdk

		defines			
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"	--Debug
        defines "HZ_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"	--Release
        defines "HZ_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"	--Dist
        defines "HZ_DIST"
		runtime "Release"
        optimize "on"

project "Hazel-Editor"
	location "Hazel-Editor"	--���·��
	kind "ConsoleApp"	--����̨Ӧ��
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	--Ŀ��Ŀ¼
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	--�м�Ŀ¼

	files				
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs			--���Ӱ���Ŀ¼
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"Hazel/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hazel"			
	}

	filter "system:windows"	--windows
        systemversion "latest"	--sdk

		defines			
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"	--Debug
        defines "HZ_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"	--Release
        defines "HZ_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"	--Dist
        defines "HZ_DIST"
		runtime "Release"
        optimize "on"