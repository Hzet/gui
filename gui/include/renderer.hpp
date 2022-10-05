#pragma once
#include <glm/glm.hpp>

#include "shader.hpp"
#include "clear-type.hpp"

namespace gui
{
	namespace internal
	{
		enum draw_type : std::uint32_t;
		class vertex_array;

		class renderer
		{
		public:
			renderer();
			virtual ~renderer() = default;

			void clear() const;
			void set_clear_color(glm::vec4 const& color);
			glm::vec4 const& get_clear_color() const;

			void set_clear_type(clear_type type);
			clear_type set_clear_type() const;

			void draw(internal::vertex_array const& v_array, internal::draw_type type) const;

		protected:
			void init();

		private:
			internal::shader m_shader;
			glm::ivec2 m_viewport;
			glm::vec4 m_clear_color;
			clear_type m_clear_type;
		};
	}
}