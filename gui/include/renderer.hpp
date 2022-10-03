#pragma once
#include "shader.hpp"

namespace gui
{
	namespace internal
	{
		enum draw_type : std::uint32_t;
		class vertex_array;

		class renderer
		{
		public:
			virtual ~renderer() = default;

			void draw(internal::vertex_array const& v_array, internal::draw_type type) const;

		protected:
			void init();

		private:
			internal::shader m_shader;
		};
	}
}