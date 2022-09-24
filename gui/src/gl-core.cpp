#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		static std::uint64_t s_last_opengl_error = GL_NO_ERROR;

		void gui::internal::opengl_clear_error()
		{
			std::uint64_t error = glGetError();

			if (error == GL_NO_ERROR)
				s_last_opengl_error = GL_NO_ERROR;
			else
				while ((error = glGetError()) != GL_NO_ERROR)
					s_last_opengl_error = error;
		}

		bool gui::internal::opengl_check_error(std::uint64_t v)
		{
			return v == GL_NO_ERROR;
		}

		std::uint64_t gui::internal::opengl_get_last_error()
		{
			return s_last_opengl_error;
		}
	}
}