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
include "dependencies/glad.lua"
include "dependencies/glm.lua"
include "game/game.lua"