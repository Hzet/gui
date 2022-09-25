#include "exception.hpp"
#include "gl-core.hpp"
#include "shader.hpp"

#include <fstream>
#include <glm/ext.hpp>

namespace gui
{
	namespace internal
	{
		static std::uint32_t compile_sub_shader(const std::string const& source);
		static std::uint32_t get_uniform_location(std::string const& name, std::uint32_t shader_index);
		static std::string read_file_content(std::string const& filepath);
		
		static std::uint32_t compile_sub_shader(const std::string const& source)
		{
			if (source.empty())
			{
				STE_EXCEPTION("Shader source code failed to compile: source code is empty");
				return false;
			}

			const char *source = source.c_str();

			create();
			AGL_CALL(glShaderSource(objectID_, 1u, &source, NULL));
			AGL_CALL(glCompileShader(objectID_));

			std::int32_t result;

			AGL_CALL(glGetShaderiv(objectID_, GL_COMPILE_STATUS, &result));

			if (!result)
			{
				std::int32_t length;
				std::string message;
				AGL_CALL(glGetShaderiv(objectID_, GL_INFO_LOG_LENGTH, &length));

				message.resize(length);
				AGL_CALL(glGetShaderInfoLog(objectID_, length, nullptr, &message[0u]));

				AGL_CORE_ERROR("Shader [{}] sub program could not be compiled!\n{}", error::SUBSHADER_COMPILE, getShaderName(type_), message);

				return false;
			}
			return true;
		}

		void shader::load_from_files(std::string const& vertex_path, std::string const& fragment_path)
		{
			auto vertex_source = read_file_content(vertex_path);
			auto fragment_source = read_file_content(fragment_path);

			compile(vertex_source, fragment_source);
		}

		void shader::bind() const
		{
			GL_CALL(glUseProgram(m_gl_index));
		}

		void shader::setUniform(const std::string &name, const float value) const
		{
			GL_CALL(glUniform1f(get_uniform_location(name, m_gl_index), value));
		}

		void shader::setUniform(const std::string &name, const std::int32_t value) const
		{
			GL_CALL(glUniform1i(get_uniform_location(name, m_gl_index), value));
		}

		void shader::setUniform(const std::string &name, const std::uint32_t value) const
		{
			GL_CALL(glUniform1ui(get_uniform_location(name, m_gl_index), value));
		}

		void shader::setUniform(const std::string &name, const glm::vec2 &value) const
		{
			GL_CALL(glUniform2f(get_uniform_location(name, m_gl_index), value.x, value.y));
		}

		void shader::setUniform(const std::string &name, const glm::vec3 &value) const
		{
			GL_CALL(glUniform3f(get_uniform_location(name, m_gl_index), value.x, value.y, value.z));
		}

		void shader::setUniform(const std::string &name, const glm::vec4 &value) const
		{
			GL_CALL(glUniform4f(get_uniform_location(name, m_gl_index), value.x, value.y, value.z, value.w));
		}

		void shader::setUniform(const std::string &name, const glm::mat4 &value) const
		{
			GL_CALL(glUniformMatrix4fv(get_uniform_location(name, m_gl_index), 1u, GL_FALSE, glm::value_ptr(value)));
		}

		void shader::setUniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const
		{
			GL_CALL(glUniform1iv(get_uniform_location(name, m_gl_index), count, value));
		}

		void compile(std::string const& vertex_source, std::string const& fragment_source)
		{
		}

		static std::uint32_t get_uniform_location(std::string const& name, std::uint32_t shader_index)
		{
			std::uint32_t result;

			GL_CALL(result = glGetUniformLocation(shader_index, name.c_str()));
			STE_ASSERT(result != -1, "Uniform with such name does not exist!\nName: {}", name);

			return result;
		}


		static std::string read_file_content(std::string const& filepath)
		{
			auto file = std::fstream{ filepath, std::ios::in };

			if (!file)
			{
				file.close();
				STE_EXCEPTION("Failed to open file: " + filepath);
			}

			auto content = std::string{};

			file.seekg(0, std::ios::end);
			content.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

			file.close();

			return content;
		}
	}
}