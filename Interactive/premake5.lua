outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "TurtleEngine"
	startproject "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

include "Engine/engine.lua"
include "Engine/dependencies/glfw.lua"
include "Engine/dependencies/glad.lua"