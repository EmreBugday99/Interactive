#pragma once

#ifdef TURTLE_OS_WINDOWS
	#ifdef TURTLE_CORE
		#define TURTLE_API __declspec(dllexport)
	#else
		#define TURTLE_API __declspec(dllimport)
	#endif
#endif