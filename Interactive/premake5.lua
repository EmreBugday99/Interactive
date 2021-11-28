outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "TurtleEngine"
	architecture "x64"
	startproject "Engine"

	configurations
	{
		"Debug",
		"Release"
	}

include "Engine/engine.lua"