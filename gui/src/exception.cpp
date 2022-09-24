#include "exception.hpp"

namespace gui
{
	exception::exception(std::string const& message)
		: m_message{ message }
	{
	}

	char const* exception::what() const
	{
		return m_message.c_str();
	}
}