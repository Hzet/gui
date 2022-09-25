#pragma once

#include <iostream>

#define STE_HALT() __debugbreak()

#define STE_ASSERT(condition, message) \
do \
{ \
	if(!(condition)) \
	{ \
		std::cerr << "Assertion failed on: " << #condition << "\nMessage: " << message << std::endl; \
		STE_HALT(); \
	} \
} while(false)