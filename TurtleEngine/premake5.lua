workspace "TurtleEngine"
	startproject "Game"
	architecture "x64"

	outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	configurations
	{
		"Debug",
		"Release"
	}

include "turtle-core/core.lua"
include "game/game.lua"
include "turtle-core/dependencies/glad.lua"