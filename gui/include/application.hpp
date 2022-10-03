#pragma once
#include <memory>
#include <string>

#include "window.hpp"

namespace gui
{
	class application;

	extern std::unique_ptr<application> create_application();

	class application
	{
	public:
		void run();
		void close(); 

	protected:
		virtual void update();

	private:
		window m_window;
	};
}