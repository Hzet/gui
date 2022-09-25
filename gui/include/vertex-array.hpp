#pragma once
#include "index-buffer.hpp"
#include "vertex-buffer.hpp"
#include "vertex-layout.hpp"

namespace gui
{
	namespace internal
	{
		class vertex_array
		{
		public:
			vertex_array();
			vertex_array(vertex_array&&);
			~vertex_array();
			vertex_array& operator=(vertex_array&&) = default;

			bool is_created() const;

			void bind() const;
			void unbind() const;
			void create();
			void destroy();

			void set_data(const vertex_buffer &buffer, const vertex_layout &layout);
			void set_data(const vertex_buffer &vbuffer, const vertex_layout &layout, const index_buffer &ibuffer);

			std::uint32_t get_index_count() const;
			std::uint32_t get_vertex_count() const;

		private:
			std::uint32_t m_gl_index;
			std::uint32_t m_index_count;
			bool m_moving;
			std::uint32_t m_vertex_count;
		};
	}
}