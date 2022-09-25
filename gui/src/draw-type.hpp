#pragma once
#include <glad/glad.h>

namespace gui
{
	namespace internal
	{
		enum draw_type : std::uint32_t
		{
			POINTS = GL_POINTS,
			LINES = GL_LINES,
			TRAINGLES = GL_TRIANGLES
		};
	}
}