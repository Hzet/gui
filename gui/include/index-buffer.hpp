#pragma once
#include <cstdint>

namespace gui
{
	namespace internal
	{
		class index_buffer final
		{
		public:
			index_buffer();

			index_buffer(index_buffer&&);
			~index_buffer();
			index_buffer& operator=(index_buffer&&) = default;

			bool is_created() const;

			void bind() const;
			void unbind() const;
			void create();
			void destroy();

			void allocate(std::uint32_t const * const data, std::uint32_t count);
			void buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count);

			std::uint32_t get_count() const;

		private:
			std::uint32_t m_count;
			std::uint32_t m_gl_index;
			bool m_moving;
		};
	}
}