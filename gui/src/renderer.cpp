#include "data-type.hpp"
#include "draw-type.hpp"
#include "renderer.hpp"
#include "gl-core.hpp"
#include "vertex-array.hpp"

namespace gui
{
	namespace internal
	{
		renderer::renderer()
			: m_clear_type{ GL_COLOR_BUFFER_BIT }
		{
		}

		void renderer::clear() const
		{
			GL_CALL(glClearColor(m_clear_color.x, m_clear_color.y, m_clear_color.z, m_clear_color.w));
			GL_CALL(glClear(m_clear_type));
		}

		void renderer::set_clear_color(glm::vec4 const& color)
		{
			m_clear_color = color;
		}

		glm::vec4 const& renderer::get_clear_color() const
		{
			return m_clear_color;
		}


		void renderer::set_clear_type(clear_type type)
		{
			m_clear_type = type;
		}


		gui::clear_type renderer::set_clear_type() const
		{
			return m_clear_type;
		}

		void renderer::draw(internal::vertex_array const& v_array, internal::draw_type type) const
		{
			v_array.bind();

			if (v_array.get_index_count() == 0)
				GL_CALL(glDrawArrays(type, 0, v_array.get_vertex_count()));
			else
				GL_CALL(glDrawElements(type, v_array.get_index_count(), internal::UINT, 0));
		}

		void renderer::init()
		{
			m_shader.load_from_files("resource//vshader.s", "resource//fshader.s");

			m_shader.bind();
		}
	}
}