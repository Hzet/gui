#include "event-manager.hpp"

namespace gui
{
	gui::event_manager::events event_manager::s_events;

	bool event_manager::key_pressed(key_type key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool event_manager::button_pressed(button_type button)
	{

	}

	glm::vec2 event_manager::get_mouse_position()
	{

	}
}