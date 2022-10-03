#pragma once
#include "clear-type.hpp"
#include "gl-core.hpp"
#include "renderer.hpp"	

#include <glm/glm.hpp>
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
		static window create(glm::ivec2 resolution, std::string const& title);

	public:
		using internal::renderer::renderer;

		window() = default;
		window(window&& other);
		window& operator=(window&& other);
		~window();

		bool is_open();
		void close();

		void display() const;
		//bool poll_event() const;


	private:
		window(glm::ivec2 resolution, std::string const &title);
		
		void open();

		static std::uint64_t s_window_count;

		std::unique_ptr<GLFWwindow, detail::glfw_window_deleter> m_handle;
		glm::uvec2 m_resolution;
		std::string m_title;
		glm::ivec2 m_viewport;
		glm::vec3 m_clear_color;
		clear_type m_clear_type;
	};
}