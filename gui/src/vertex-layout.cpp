#include "vertex-layout.hpp"
#include "debug.hpp"

namespace gui
{
	namespace internal
	{
		vertex_layout::vertex_layout()
			: m_stride{ 0ul }
		{
		}

		std::uint32_t vertex_layout::get_size() const
		{
			return m_stride;
		}

		std::uint32_t vertex_layout::get_count() const
		{
			return m_element.size();
		}

		const vertex_layout::element& vertex_layout::operator[](const std::uint32_t index) const
		{
			STE_ASSERT(index < m_element.size(), "Index out of bounds!");

			return m_element[index];
		}
	}
}