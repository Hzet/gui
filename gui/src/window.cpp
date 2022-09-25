#include "window.hpp"
#include "exception.hpp"

#include <iostream>
#include <iomanip>

namespace gui
{
	namespace detail
	{
		void glfw_window_deleter::operator()(GLFWwindow* ptr)
		{
			glfwDestroyWindow(ptr);
		}
	}

	namespace internal
	{
		static void framebuffer_size_callback(GLFWwindow* handle, int width, int height);
		static void glfw_error_callback(int error, char const* msg);
	}

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

	bool window::update()
	{
		glfwSwapBuffers(m_handle.get());
		glfwPollEvents();

		return !glfwWindowShouldClose(m_handle.get());
	}

	void window::close()
	{
		if (m_handle != nullptr)
			glfwTerminate();
	}

	window::window(glm::ivec2 resolution, std::string const & title)
		: m_resolution{ resolution }
		, m_title{ title }
	{
	}

	void window::open()
	{
		if(!glfwInit())
		{
			STE_EXCEPTION("Failed to create GLFW window");
		}

		glfwSetErrorCallback(internal::glfw_error_callback);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_handle = std::unique_ptr<GLFWwindow, detail::glfw_window_deleter>(glfwCreateWindow(m_resolution.x, m_resolution.y, m_title.c_str(), nullptr, nullptr));

		if(m_handle == nullptr)
		{
			auto i = glfwGetError(nullptr);

			std::cout << std::hex << i << std::endl;
			STE_EXCEPTION("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(m_handle.get());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			STE_EXCEPTION("Failed to initialize GLAD");
		}

		glfwSetFramebufferSizeCallback(m_handle.get(), internal::framebuffer_size_callback);
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