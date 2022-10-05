#include "application.hpp"
#include "exception.hpp"

#include <GLFW/glfw3.h>

namespace gui
{
	application application::s_application;

	void application::process_window_events()
	{
		event e;
		while (m_window->poll_event(e))
		{
			switch (e.type)
			{
			case WINDOW_CLOSED:
				m_window->close();
				break;
			}
		}
	}

	application& application::get_application()
	{
		static auto app = create_application();

		return *app;
	}

	void application::create(glm::ivec2 const& resolution, std::string const& title)
	{
		m_window = std::make_unique<window>();
		m_window->open(resolution, title);

		if (!m_window->is_open())
			GUI_EXCEPTION("Failed to open window");
	}

	void application::run()
	{
		while (m_window->is_open())
		{
			glfwPollEvents();

			process_window_events();

			if (!m_window->is_open())
				break;

			m_window->display();
		}

		close();
	}

	void application::close()
	{
		m_window->close();
	}

	window& application::get_window()
	{
		return *m_window;
	}
}