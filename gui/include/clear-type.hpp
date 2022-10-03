#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace gui
{
	enum clear_type : std::uint32_t
	{
		CLEAR_COLOR = GL_COLOR_BUFFER_BIT,
		CLEAR_DEPTH = GL_DEPTH_BUFFER_BIT,
		CLEAR_STENCIL = GL_STENCIL_BUFFER_BIT
	};
}