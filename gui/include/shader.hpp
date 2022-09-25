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
			void load_from_files(std::string const& vertex_path, std::string const& fragment_path);

			void bind() const;

			void setUniform(const std::string &name, const float value) const;
			void setUniform(const std::string &name, const std::int32_t value) const;
			void setUniform(const std::string &name, const std::uint32_t value) const;
			void setUniform(const std::string &name, const glm::vec2 &value) const;
			void setUniform(const std::string &name, const glm::vec3 &value) const;
			void setUniform(const std::string &name, const glm::vec4 &value) const;
			void setUniform(const std::string &name, const glm::mat4 &value) const;
			void setUniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const;

		private:
			void compile(std::string const& vertex_source, std::string const& fragment_source);

		private:
			std::uint32_t m_gl_index;

		};
	}
}