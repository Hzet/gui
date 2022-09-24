#pragma once
#include <exception>
#include <string>

#include "debug.hpp"

#ifdef STE_DEBUG
#include <iostream>
#define STE_EXCEPTION(message) \
do \
{ \
	std::cerr << "Exception raised!\nMessage: " << message << std::endl; \
	STE_HALT(); \
} while(false)
#else
#define STE_EXCEPTION(message) throw ::gui::exception{ message }
#endif

namespace gui
{
	class exception
		: public std::exception
	{
	public:
		exception() = default;
		exception(std::string const& message);
		virtual ~exception() = default;

		virtual char const* what() const override;

	private:
		std::string m_message;
	};
}