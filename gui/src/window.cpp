#include "window.hpp"
#include "exception.hpp"
#include <iostream>
#include <iomanip>
#include <glfw/glfw3.h>

namespace gui
{
	namespace detail
	{
		void glfw_window_deleter::operator()(GLFWwindow* ptr)
		{
		}
	}

	namespace internal
	{
		static void framebuffer_size_callback(GLFWwindow* handle, int width, int height);
		static void glfw_error_callback(int error, char const* msg);
	}

	std::uint64_t window::s_window_count = 0;

	window window::create(glm::ivec2 resolution, std::string const& title)
	{
		auto handle = window{ resolution, title };

		handle.open();

		return handle;
	}

	window::~window()
	{
		close();
	}

	bool window::is_open()
	{
		return !glfwWindowShouldClose(m_handle.get());
	}

	void window::close()
	{
		if (m_handle != nullptr)
		{
			glfwDestroyWindow(m_handle.get());
			--s_window_count;

			if(s_window_count == 0)
				glfwTerminate();
		}
	}

	void window::display() const
	{
		glfwSwapBuffers(m_handle.get());

		GL_CALL(glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, 1.f));
		GL_CALL(glClear(m_clear_type));
	}

	window::window(glm::ivec2 resolution, std::string const & title)
		: m_resolution{ resolution }
		, m_title{ title }
	{
	}


	window::window(window&& other)
		: m_handle{ std::move(other.m_handle) }
		, m_resolution{ std::move(other.m_resolution) }
		, m_title{ std::move(other.m_title)}
		, m_viewport{ std::move(other.m_viewport) }
		, m_clear_color{ std::move(other.m_clear_color) }
	    , m_clear_type{ other.m_clear_type }
	{
	}

	window& window::operator=(window&& other)
	{
		m_handle = std::move(other.m_handle);
		m_resolution = std::move(other.m_resolution);
		m_title = std::move(other.m_title);
		m_viewport = std::move(other.m_viewport);
		m_clear_color = std::move(other.m_clear_color);
		m_clear_type = other.m_clear_type;

		return *this;
	}

	void window::open()
	{
		if(!glfwInit())
		{
			GUI_EXCEPTION("Failed to create GLFW window");
		}

		glfwSetErrorCallback(internal::glfw_error_callback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_handle = std::unique_ptr<GLFWwindow, detail::glfw_window_deleter>(glfwCreateWindow(m_resolution.x, m_resolution.y, m_title.c_str(), nullptr, nullptr));

		if(m_handle == nullptr)
		{
			auto i = glfwGetError(nullptr);

			std::cout << std::hex << i << std::endl;
			GUI_EXCEPTION("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(m_handle.get());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			GUI_EXCEPTION("Failed to initialize GLAD");
		}

		++s_window_count;

		glfwSetFramebufferSizeCallback(m_handle.get(), internal::framebuffer_size_callback);

		internal::renderer::init();
	}

	namespace internal
	{
		static void framebuffer_size_callback(GLFWwindow* handle, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		static void glfw_error_callback(int error, char const* msg)
		{
			std::cout << "GLFW Error: " << msg << std::endl;
		}
	}
}