#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "gl-core.hpp"

namespace gui
{
	namespace internal
	{
		class vertex_layout
		{
		public:
			struct element
			{
				std::uint32_t type;
				std::uint32_t size;
				std::uint32_t count;
				std::uint32_t offset;
				bool normalized;
			};
		public:
			vertex_layout();

			std::uint32_t get_size() const;
			std::uint32_t get_count() const;

			const element& operator[](const std::uint32_t index) const;

			template <class T>
			void add_element();

		private:
			template <class T> element get_element() const;
			template <> element get_element<std::uint8_t>() const;
			template <> element get_element<std::uint32_t>() const;
			template <> element get_element<float>() const;
			template <> element get_element<glm::vec2>() const;
			template <> element get_element<glm::vec3>() const;
			template <> element get_element<glm::vec4>() const;

			static constexpr std::uint32_t get_type_size(const std::uint32_t type);

			std::uint32_t m_stride;
			std::vector<element> m_element;
		};

#include "vertex-layout.inl"
	}
}