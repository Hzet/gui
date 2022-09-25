#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace gui
{
	namespace internal
	{
		enum data_type : std::uint32_t
		{
			UINT = GL_UNSIGNED_INT,
		};
	}
}