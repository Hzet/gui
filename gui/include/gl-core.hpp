#pragma once
#include <string>
#include <glad/glad.h>

#include "debug.hpp"

#define GL_CALL(instruction) \
do \
{ \
	::gui::internal::opengl_clear_error(); \
	instruction; \
\
	GUI_ASSERT(::gui::internal::opengl_check_error(::gui::internal::opengl_get_last_error()), "Failed to execute OpenGL call: " + std::to_string(::gui::internal::opengl_get_last_error())); \
} while(false)


namespace gui
{
	namespace internal
	{
		void opengl_clear_error();

		bool opengl_check_error(std::uint32_t v);

		std::uint32_t opengl_get_last_error();
	}
}