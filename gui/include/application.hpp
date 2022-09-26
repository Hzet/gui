#pragma once
#include <memory>
#include <string>

#include "renderer.hpp"
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
		virtual bool should_update();

	private:
		renderer m_renderer;
		window m_window;
	};
}