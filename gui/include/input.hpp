#pragma once
#include <glm/glm.hpp>
#include "event-type.hpp"

namespace gui
{
	class input
	{
	public:
		static bool key_pressed(key_type key);
		static bool button_pressed(button_type button);
		static bool mouse_moved();
		static glm::vec2 get_mouse_position();
	};
}