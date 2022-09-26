#pragma once
#include "shader.hpp"

namespace gui
{
	namespace internal
	{
		enum draw_type;
		class vertex_array;
	}

	class renderer
	{
	public:
		void draw(internal::vertex_array const& v_array, internal::draw_type type) const;

	private:
		friend class application;

	private:
		void init();

	private:
		internal::shader m_shader;
	};
}