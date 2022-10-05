#pragma once
#include <queue>
#include <glm/glm.hpp>

#include "event.hpp"

namespace gui
{
	struct window_data
	{
		bool closed;
		glm::vec2 content_scale;
		std::queue<event> events;
		glm::vec2 framebuffer_size;
		bool focused;
		bool maximized;
		bool minimized;
		glm::vec2 resolution;
		std::string title;
	};
}