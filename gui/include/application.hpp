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
		static application& get_application();

		void create(glm::ivec2 const& resolution, std::string const& name);
		void close(); 
		void run();

		window& get_window();

	private:
		static application s_application;

		void process_window_events();

		std::unique_ptr<window> m_window;
	};
}