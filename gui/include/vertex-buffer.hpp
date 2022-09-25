#pragma once
#include <cstdint>
#include <cstddef>

namespace gui
{
	namespace internal
	{
		class vertex_buffer
		{
		public:
			vertex_buffer();
			vertex_buffer(vertex_buffer&&);
			vertex_buffer& operator=(vertex_buffer&&) = default;
			~vertex_buffer();

			void bind() const;
			void unbind() const;

			bool is_created() const;
			void create();
			void destroy();
			void allocate(std::byte const * const data, const std::uint32_t size, const std::uint32_t count); // data, overall size, vertex count (amount of strides)
			void buffer(void const * const data, const std::uint32_t offset, const std::uint32_t size);

			std::uint32_t get_size() const;
			std::uint32_t get_count() const;

		private:
			std::uint32_t m_count;
			std::uint32_t m_gl_index;
			bool m_moving;
			std::uint32_t m_size;
		};

	}
}