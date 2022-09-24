#pragma once
#include "gl-core.hpp"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace gui
{
	namespace detail
	{
		class glfw_window_deleter
		{
		public:
			void operator()(GLFWwindow* ptr);
		};
	}

	class window
	{
	public:
		static window create(glm::ivec2 resolution, std::string const& title);

	public:
		window() = default;
		window(window&&) = default;
		window& operator=(window&&) = default;
		~window();

		bool update();
		void close();

	private:
		window(glm::ivec2 resolution, std::string const &title);
		
		void open();

		std::unique_ptr<GLFWwindow, detail::glfw_window_deleter> m_handle;
		glm::uvec2 m_resolution;
		std::string m_title;
		glm::ivec2 m_viewport;
	};
}