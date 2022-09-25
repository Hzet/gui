#include "vertex-array.hpp"
#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		vertex_array::vertex_array()
			: m_gl_index{ 0u }
			, m_index_count{ 0u }
			, m_vertex_count{ 0u }
			, m_moving{ false }
		{
		}

		vertex_array::vertex_array(vertex_array&& other)
			: m_gl_index{ other.m_gl_index }
			, m_index_count{ other.m_index_count }
			, m_vertex_count{ other.m_vertex_count }
			, m_moving{ true }
		{
		}

		vertex_array::~vertex_array()
		{
			if (!m_moving)
				destroy();
		}

		bool vertex_array::is_created() const
		{
			return m_gl_index != 0u;
		}

		void vertex_array::bind() const
		{
			GL_CALL(glBindVertexArray(m_gl_index));
		}

		void vertex_array::unbind() const
		{
			GL_CALL(glBindVertexArray(0u));
		}

		void vertex_array::create()
		{
			if (is_created())
				destroy();

			GL_CALL(glGenVertexArrays(1u, &m_gl_index));
		}

		void vertex_array::destroy()
		{
			GL_CALL(glDeleteVertexArrays(1u, &m_gl_index));

			m_gl_index = 0u;
			m_index_count = 0u;
			m_vertex_count = 0u;
		}

		void vertex_array::set_data(const vertex_buffer &vBuffer, const vertex_layout &layout)
		{
			m_vertex_count = vBuffer.get_count();

			vBuffer.bind();
			create();
			bind();

			auto offset = 0u;

			for (auto i = 0u; i < layout.get_count(); i++)
			{
				GL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, layout.get_size(), reinterpret_cast<void*>(offset)));
				GL_CALL(glEnableVertexAttribArray(i));
				offset += layout[i].size;
			}
		}

		void vertex_array::set_data(const vertex_buffer &vbuffer, const vertex_layout &layout, const index_buffer &ibuffer)
		{
			m_vertex_count = vbuffer.get_count();
			m_index_count = ibuffer.get_count();

			create();

			bind();
			vbuffer.bind();
			ibuffer.bind();

			auto offset = 0u;

			for (auto i = 0u; i < layout.get_count(); i++)
			{
				GL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized ? GL_TRUE : GL_FALSE, layout.get_size(), reinterpret_cast<void*>(offset)));
				GL_CALL(glEnableVertexAttribArray(i));
				offset += layout[i].size;
			}
		}

		std::uint32_t vertex_array::get_index_count() const
		{
			return m_index_count;
		}

		std::uint32_t vertex_array::get_vertex_count() const
		{
			return m_vertex_count;
		}

	}
}