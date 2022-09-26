#pragma once
#include <string>
#include <glm/glm.hpp>
namespace gui
{
	namespace internal
	{
		class shader
		{
		public:
			shader();
			shader(shader&& other);
			shader& operator=(shader&&) = default;
			~shader();

			void load_from_files(std::string const& vertex_path, std::string const& fragment_path);

			bool is_created() const;

			void destroy();
			void bind() const;

			void set_uniform(const std::string &name, const float value) const;
			void set_uniform(const std::string &name, const std::int32_t value) const;
			void set_uniform(const std::string &name, const std::uint32_t value) const;
			void set_uniform(const std::string &name, const glm::vec2 &value) const;
			void set_uniform(const std::string &name, const glm::vec3 &value) const;
			void set_uniform(const std::string &name, const glm::vec4 &value) const;
			void set_uniform(const std::string &name, const glm::mat4 &value) const;
			void set_uniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const;

		private:
			std::uint32_t m_gl_index;
			bool m_moving;
		};
	}
}