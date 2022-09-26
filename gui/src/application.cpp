#include "application.hpp"

namespace gui
{
	void application::run()
	{
		m_window = window::create({ 1280, 1024 }, "Application");

		m_renderer = renderer{};
		m_renderer.init();

		while (should_update())
		{
			this->update();
		}
	}

	void application::close()
	{
		m_window.close();
	}

	void application::update()
	{

	}

	bool application::should_update()
	{
		return m_window.update();
	}
}