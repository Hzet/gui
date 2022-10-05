#pragma once
#include <glm/glm.hpp>

#include "event.hpp"

namespace gui
{
	class event_manager
	{
	public:
		static bool key_pressed(key_type key);
		static bool button_pressed(button_type button);
		static glm::vec2 get_mouse_position();

	private:
		struct events
		{
			bool m_event_type[18];
			bool m_key_code[348];
			bool m_button_type[7];
		};

	private:
		static events s_events;
	};
}