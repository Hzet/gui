#pragma once
#include "event-type.hpp"

namespace gui
{
	struct event
	{
		struct position_factor
		{
			double x;
			double y;
		};

		struct size_factor
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		struct scroll_factor
		{
			double x;
			double y;
		};

		struct keyboard
		{
			key_type key_code;
			std::int32_t scancode;
			std::int32_t modifiers;
		};

		struct mouse
		{
			button_type code;
			std::int32_t bit_modifiers;
		};

		struct scale_factor
		{
			float x;
			float y;
		};

		event_type type = INVALID_EVENT;

		union
		{
			mouse button;
			keyboard key;
			position_factor position;
			scale_factor scale;
			scroll_factor scroll;
			size_factor size;
			std::uint32_t character;
		};
	};
}