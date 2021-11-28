outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "TurtleEngine"
	architecture "x64"
	startproject "Engine"

	configurations
	{
		"Debug",
		"Release"
	}

include "Engine/dependencies/glfw.lua"
include "Engine/dependencies/glad.lua"
include "Engine/engine.lua"