#include "index-buffer.hpp"
#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		index_buffer::index_buffer()
			: m_count{ 0u }
			, m_gl_index{ 0u }
			, m_moving{ false }
		{
		}

		index_buffer::index_buffer(index_buffer&& other)
			: m_count{ other.m_count }
			, m_gl_index{ other.m_gl_index }
			, m_moving{ true }
		{
		}

		index_buffer::~index_buffer()
		{
			if (!m_moving)
				destroy();
		}

		bool index_buffer::is_created() const
		{
			return m_gl_index != 0u;
		}

		void index_buffer::bind() const
		{
			GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_index));
		}

		void index_buffer::unbind() const
		{
			GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u));
		}

		void index_buffer::create()
		{
			if (is_created())
				destroy();

			GL_CALL(glGenBuffers(1u, &m_gl_index));
		}

		void index_buffer::destroy()
		{
			GL_CALL(glDeleteBuffers(1u, &m_gl_index));

			m_gl_index = 0u;
			m_count = 0u;
		}

		void index_buffer::allocate(std::uint32_t const * const data, std::uint32_t count)
		{
			STE_ASSERT(count != 0u, "Can not allocate no memory!");
			STE_ASSERT(m_count == 0u, "Overriding previous allocation!");

			create();
			bind();

			m_count = count;
			GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(std::uint32_t), data, GL_STATIC_DRAW));
		}

		void index_buffer::buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count)
		{
			STE_ASSERT(count != 0u, "Buffering data of zero size!");
			STE_ASSERT(m_count != 0u, "Buffer has not been allocated yet!");
			STE_ASSERT(offset + count < m_count, "Overflowing buffer size!");

			bind();
			GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(std::uint32_t), count * sizeof(std::uint32_t), data));
		}

		std::uint32_t index_buffer::get_count() const
		{
			return m_count;
		}
	}
}