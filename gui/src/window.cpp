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
		static void glfw_error_callback(int error, char const* msg);
		static void glfw_framebuffer_size_callback(GLFWwindow* handle, int width, int height);
		static void glfw_set_callbacks(GLFWwindow *handle);
		static void glfw_window_button_input_callback(GLFWwindow *window, int button, int action, int mods);
		static void glfw_window_char_callback(GLFWwindow *window, unsigned int codepoint);
		static void glfw_window_close_callback(GLFWwindow *window);
		static void glfw_window_cursor_enter_callback(GLFWwindow *window, int entered);
		static void glfw_window_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		static void glfw_window_focus_callback(GLFWwindow *window, int focused);
		static void glfw_window_framebuffer_size_callback(GLFWwindow *window, int width, int height);
		static void glfw_window_iconify_callback(GLFWwindow *window, int iconified);
		static void glfw_window_key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void glfw_window_maximize_callback(GLFWwindow *window, int maximnized);
		static void glfw_window_scale_callback(GLFWwindow *window, float xscale, float yscale);
		static void glfw_window_scroll_input_callback(GLFWwindow *window, double xoffset, double yoffset);
		static void glfw_window_size_callback(GLFWwindow *window, int width, int height);
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
		clear();

		glfwSwapBuffers(m_handle.get());
	}

	bool window::poll_event(event& e)
	{
		if (m_data.events.empty())
			return false;

		e = m_data.events.front();
		m_data.events.pop();
		return true;
	}

	window::window(glm::ivec2 resolution, std::string const & title)
	{
		m_data.resolution = resolution;
		m_data.title = title;
	}

	window::window(window&& other)
		: m_handle{ std::move(other.m_handle) }
		, m_data{ std::move(other.m_data) }
	{
	}

	window& window::operator=(window&& other)
	{
		m_handle = std::move(other.m_handle);
		m_data = std::move(other.m_data);

		return *this;
	}

	void window::open()
	{
		if (s_window_count == 0)
		{
			if (!glfwInit())
			{
				GUI_EXCEPTION("Failed to create GLFW window");
			}

			glfwSetErrorCallback(internal::glfw_error_callback);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		m_handle = std::unique_ptr<GLFWwindow, detail::glfw_window_deleter>(glfwCreateWindow(m_data.resolution.x, m_data.resolution.y, m_data.title.c_str(), nullptr, nullptr));

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

		init();
		internal::glfw_set_callbacks(m_handle.get());
		glfwSetWindowUserPointer(m_handle.get(), reinterpret_cast<void*>(&m_data));

		++s_window_count;
	}

	namespace internal
	{
		void glfw_set_callbacks(GLFWwindow *handle)
		{
			glfwSetCharCallback(handle, glfw_window_char_callback);
			glfwSetCursorEnterCallback(handle, glfw_window_cursor_enter_callback);
			glfwSetCursorPosCallback(handle, glfw_window_cursor_position_callback);
			glfwSetFramebufferSizeCallback(handle, glfw_window_framebuffer_size_callback);
			glfwSetKeyCallback(handle, glfw_window_key_input_callback);
			glfwSetMouseButtonCallback(handle, glfw_window_button_input_callback);
			glfwSetScrollCallback(handle, glfw_window_scroll_input_callback);
			glfwSetWindowCloseCallback(handle, glfw_window_close_callback);
			glfwSetWindowContentScaleCallback(handle, glfw_window_scale_callback);
			glfwSetWindowFocusCallback(handle, glfw_window_focus_callback);
			glfwSetWindowIconifyCallback(handle, glfw_window_iconify_callback);
			glfwSetWindowMaximizeCallback(handle, glfw_window_maximize_callback);
			glfwSetWindowSizeCallback(handle, glfw_window_size_callback);
		}

		void glfw_framebuffer_size_callback(GLFWwindow* handle, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void glfw_error_callback(int error, char const* msg)
		{
			std::cout << "GLFW Error: " << msg << std::endl;
		}

		void glfw_window_button_input_callback(GLFWwindow *window, int button, int action, int mods)
		{
			auto &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			switch (action)
			{
			case GLFW_PRESS:
				e.type = MOUSE_KEY_PRESSED;
				break;
			case GLFW_RELEASE:
				e.type = MOUSE_KEY_RELEASED;
				break;
			}

			e.button.code = static_cast<button_type>(button);
			e.button.bit_modifiers = mods;

			data.events.push(e);
		}

		void glfw_window_char_callback(GLFWwindow *window, unsigned int codepoint)
		{
			auto &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			e.type = TEXT_ENTERED;
			e.character = codepoint;

			data.events.push(e);
		}

		void glfw_window_close_callback(GLFWwindow *window)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			data.closed = true;

			event e;
			e.type = WINDOW_CLOSED;

			data.events.push(e);
		}

		void glfw_window_cursor_enter_callback(GLFWwindow *window, int entered)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			e.type = entered ? MOUSE_ENTERED : MOUSE_LEFT;

			data.events.push(e);
		}

		void glfw_window_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			e.type = MOUSE_MOVED;
			e.position = { xpos, ypos };

			data.events.push(e);
		}

		void glfw_window_focus_callback(GLFWwindow *window, int focused)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			data.focused = true;

			event e;
			e.type = focused ? WINDOW_GAINED_FOCUS : WINDOW_LOST_FOCUS;

			data.events.push(e);
		}

		void glfw_window_framebuffer_size_callback(GLFWwindow *window, int width, int height)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			data.framebuffer_size.x = width;
			data.framebuffer_size.y = height;

			GL_CALL(glViewport(0, 0, width, height));
		}

		void glfw_window_iconify_callback(GLFWwindow *window, int iconified)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			if (iconified)
				data.minimized = true;
			else
				data.minimized = false;

			event e;
			e.type = iconified ? WINDOW_MINIMIZED : WINDOW_RESTORED;

			data.events.push(e);
		}

		void glfw_window_key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			switch (action)
			{
			case GLFW_PRESS:
				e.type = KEY_PRESSED;
				break;
			case GLFW_RELEASE:
				e.type = KEY_RELEASED;
				break;
			case GLFW_REPEAT:
				e.type = KEY_REPEATED;
				break;
			}

			e.key.key_code = static_cast<key_type>(key);
			e.key.scancode = scancode;
			e.key.modifiers = mods;

			data.events.push(e);
		}

		void glfw_window_maximize_callback(GLFWwindow *window, int maximnized)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			data.minimized = false;
			data.maximized = true;

			event e;
			e.type = maximnized ? WINDOW_MAXIMIZED : WINDOW_RESTORED;

			data.events.push(e);
		}

		void glfw_window_scale_callback(GLFWwindow *window, float xscale, float yscale)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			if (xscale == 0.f && yscale == 0.f)
			{
				data.maximized = false;
				data.minimized = true;
			}

			event e;
			e.type = WINDOW_RESCALED;
			e.scale = { xscale, yscale };

			data.events.push(e);
		}

		void glfw_window_scroll_input_callback(GLFWwindow *window, double xoffset, double yoffset)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			event e;
			e.type = MOUSE_SCROLL_MOVED;
			e.scroll = { xoffset, yoffset };

			data.events.push(e);
		}

		void glfw_window_size_callback(GLFWwindow *window, int width, int height)
		{
			window_data &data = *reinterpret_cast<window_data*>(glfwGetWindowUserPointer(window));

			if (width == 0 && height == 0)
			{
				data.maximized = false;
				data.minimized = true;
			}

			event e;
			e.type = WINDOW_RESIZED;
			e.size = { static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) };

			data.events.push(e);
		}

/*
#ifdef GUI_DEBUG
		void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
		{
			if (severity = GL_DEBUG_SEVERITY_HIGH)
			{
				GUI_EXCEPTION("source: " + std::to_string(source) + "\n" +
					"type: " + std::to_string(type) + "\n" +
					"id" + std::to_string(id) + "\n" +
					"severity: " + std::to_string(severity) + "\n" +
					"message: " + message + "\n");
			}
			else
			{
				GUI_ASSERT(false, "OpenGL error:\nsource: " + std::to_string(source) + "\n" +
					"type: " + std::to_string(type) + "\n" +
					"id" + std::to_string(id) + "\n" +
					"severity: " + std::to_string(severity) + "\n" +
					"message: " + message + "\n");
			}
		}
#endif*/
	}
}