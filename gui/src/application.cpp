#include "application.hpp"

namespace gui
{
	void application::run()
	{
		m_window = window::create({ 1280, 1024 }, "Application");
		
		while (m_window.is_open())
		{
			this->update();

			m_window.display();
		}
	}

	void application::close()
	{
		m_window.close();
	}

	void application::update()
	{
	}
}