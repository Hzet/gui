#pragma once
#include <exception>
#include <string>

#include "debug.hpp"

#ifdef GUI_DEBUG
#define GUI_EXCEPTION(message) GUI_ASSERT(false, message);
#else
#define GUI_EXCEPTION(message) throw ::gui::exception{ message }
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