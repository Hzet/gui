#include "application.hpp"

namespace gui
{
	void application::run()
	{
		while (should_update())
		{
			this->update();
		}
	}

	void application::update()
	{

	}

	bool application::should_update() const
	{
		return true;
	}
}