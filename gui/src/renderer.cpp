#include "data-type.hpp"
#include "draw-type.hpp"
#include "renderer.hpp"
#include "gl-core.hpp"
#include "vertex-array.hpp"

namespace gui
{
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
		m_shader.load_from_files("vshader.s", "fshader.s");

		m_shader.bind();
	}
}