#pragma once
#include <string>

#if (CROSS_MODE_BUILD)
	#if (WIN32)
		#define CROSS_NATIVE __declspec(dllexport)
	#else
		#define CROSS_NATIVE
	#endif
#elif (CROSS_MODE_USE)
	#if (WIN32)
		#define CROSS_NATIVE __declspec(dllimport)
	#else
		#define CROSS_NATIVE extern
	#endif
#endif

struct CrossWindow{};

CROSS_NATIVE void something();

CROSS_NATIVE std::string get_active_window_title();

CROSS_NATIVE CrossWindow* get_window_by_title(std::string title);