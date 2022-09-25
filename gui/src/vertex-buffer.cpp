#include "vertex-buffer.hpp"
#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		vertex_buffer::vertex_buffer()
			: m_count{ 0u }
			, m_gl_index{ 0u }
			, m_size{ 0u }
			, m_moving{ false }
		{
		}

		vertex_buffer::vertex_buffer(vertex_buffer&& other)
			: m_count{ other.m_count }
			, m_gl_index{ other.m_gl_index }
			, m_size{ other.m_size }
			, m_moving{ true }
		{
		}

		vertex_buffer::~vertex_buffer()
		{
			if (!m_moving)
				destroy();
		}

		void vertex_buffer::bind() const
		{
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_gl_index));
		}

		void vertex_buffer::unbind() const
		{
			GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0u));
		}

		bool vertex_buffer::is_created() const
		{
			return m_gl_index != 0u;
		}

		void vertex_buffer::create()
		{
			if (is_created())
				destroy();

			GL_CALL(glGenBuffers(1u, &m_gl_index));
		}

		void vertex_buffer::destroy()
		{
			GL_CALL(glDeleteBuffers(1u, &m_gl_index));

			m_size = 0u;
			m_count = 0u;
			m_gl_index = 0u;
		}

		void vertex_buffer::allocate(std::byte const * const data, const std::uint32_t size, const std::uint32_t count)
		{
			STE_ASSERT(size != 0u, "Reserving an empty buffer!");
			STE_ASSERT(count != 0u, "Count is required!");

			create();
			bind();

			m_size = size;
			m_count = count;

			GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}

		void vertex_buffer::buffer(void const * const data, const std::uint32_t offset, const std::uint32_t size)
		{
			STE_ASSERT(data != nullptr, "Can not set nullptr data!");
			STE_ASSERT(offset + size <= get_size(), "Buffer overflow!");

			bind();

			GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
		}

		std::uint32_t vertex_buffer::get_size() const
		{
			return m_size;
		}

		std::uint32_t vertex_buffer::get_count() const
		{
			return m_count;
		}
	}
}