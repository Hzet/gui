#pragma once
#include "event.hpp"
#include "gl-core.hpp"
#include "renderer.hpp"	
#include "window-data.hpp"

#include <string>

struct GLFWwindow;

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
		: public internal::renderer
	{
	public:
		using internal::renderer::renderer;

		window() = default;
		window(window&& other);
		window(window const&) = delete;
		window& operator=(window&& other);
		window& operator=(window const&) = delete;
		~window();

		void open(glm::ivec2 const& resolution, std::string const& title);
		bool is_open();
		void close();

		void display() const;
		bool poll_event(event& e);

		GLFWwindow* get_handle();

	private:
		window(glm::ivec2 resolution, std::string const &title);

		static std::uint64_t s_window_count;

		std::unique_ptr<GLFWwindow, detail::glfw_window_deleter> m_handle;
		window_data m_data;
	};
}