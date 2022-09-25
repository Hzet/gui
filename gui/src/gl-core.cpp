#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		static std::uint32_t s_last_opengl_error = GL_NO_ERROR;

		void opengl_clear_error()
		{
			std::uint32_t error = glGetError();

			if (error == GL_NO_ERROR)
				s_last_opengl_error = GL_NO_ERROR;
			else
				while ((error = glGetError()) != GL_NO_ERROR)
					s_last_opengl_error = error;
		}

		bool opengl_check_error(std::uint32_t v)
		{
			return v == GL_NO_ERROR;
		}

		std::uint32_t opengl_get_last_error()
		{
			return s_last_opengl_error;
		}
	}
}