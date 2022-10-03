#pragma once

#include <iostream>

#ifdef GUI_DEBUG

#define GUI_HALT() __debugbreak()
#define GUI_ASSERT(condition, message) \
do \
{ \
	if(!(condition)) \
	{ \
		std::cerr << "Assertion failed on: " << #condition << "\nMessage: " << message << std::endl; \
		GUI_HALT(); \
	} \
} while(false)

#else

#define GUI_ASSERT(condition, message) \
		do { \
			(void)sizeof(condition); \
		} while(false)

#endif
