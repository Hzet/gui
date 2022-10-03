#include "shader-type.hpp"
#include "exception.hpp"
#include "gl-core.hpp"
#include "shader.hpp"
#include <string.h>
#include <fstream>
#include <glm/ext.hpp>

namespace gui
{
	namespace internal
	{
		static std::uint32_t compile_shader_program(std::string const& vertex_path, std::string const& fragment_path);
		static std::uint32_t get_uniform_location(std::string const& name, std::uint32_t shader_index);
		static std::uint32_t load_sub_shader(std::string const& filepath, shader_type type);
		static std::string read_file_content(std::string const& filepath);
		
		shader::shader()
			: m_gl_index{ 0u }
			, m_moving{ false }
		{
		}

		shader::shader(shader&& other)
			: m_gl_index{ other.m_gl_index }
			, m_moving{ true }
		{
		}

		shader::~shader()
		{
			if (!m_moving)
				destroy();
		}

		void shader::load_from_files(std::string const& vertex_path, std::string const& fragment_path)
		{
			m_gl_index = compile_shader_program(vertex_path, fragment_path);
		}

		bool shader::is_created() const
		{
			return m_gl_index == 0;
		}

		void shader::destroy()
		{
			if(is_created())
				GL_CALL(glDeleteShader(m_gl_index));

			m_gl_index = 0;
		}

		void shader::bind() const
		{
			GL_CALL(glUseProgram(m_gl_index));
		}

		void shader::set_uniform(const std::string &name, const float value) const
		{
			GL_CALL(glUniform1f(get_uniform_location(name, m_gl_index), value));
		}

		void shader::set_uniform(const std::string &name, const std::int32_t value) const
		{
			GL_CALL(glUniform1i(get_uniform_location(name, m_gl_index), value));
		}

		void shader::set_uniform(const std::string &name, const std::uint32_t value) const
		{
			GL_CALL(glUniform1ui(get_uniform_location(name, m_gl_index), value));
		}

		void shader::set_uniform(const std::string &name, const glm::vec2 &value) const
		{
			GL_CALL(glUniform2f(get_uniform_location(name, m_gl_index), value.x, value.y));
		}

		void shader::set_uniform(const std::string &name, const glm::vec3 &value) const
		{
			GL_CALL(glUniform3f(get_uniform_location(name, m_gl_index), value.x, value.y, value.z));
		}

		void shader::set_uniform(const std::string &name, const glm::vec4 &value) const
		{
			GL_CALL(glUniform4f(get_uniform_location(name, m_gl_index), value.x, value.y, value.z, value.w));
		}

		void shader::set_uniform(const std::string &name, const glm::mat4 &value) const
		{
			GL_CALL(glUniformMatrix4fv(get_uniform_location(name, m_gl_index), 1u, GL_FALSE, glm::value_ptr(value)));
		}

		void shader::set_uniform(const std::string &name, std::int32_t const * const value, std::uint64_t count) const
		{
			GL_CALL(glUniform1iv(get_uniform_location(name, m_gl_index), count, value));
		}

		std::uint32_t compile_shader_program(std::string const& vertex_path, std::string const& fragment_path)
		{
			auto vertex_index = load_sub_shader(vertex_path, VERTEX);
			auto fragment_index = load_sub_shader(fragment_path, FRAGMENT);
			auto shader_index = std::uint32_t{};

			GL_CALL(shader_index = glCreateProgram());
			GL_CALL(glAttachShader(shader_index, vertex_index));
			GL_CALL(glAttachShader(shader_index, fragment_index));

			GL_CALL(glLinkProgram(shader_index));

			GL_CALL(glDeleteShader(vertex_index));
			GL_CALL(glDeleteShader(fragment_index));

			std::int32_t result;
			GL_CALL(glGetProgramiv(shader_index, GL_LINK_STATUS, &result));

			if (!result)
			{
				std::int32_t length;
				GL_CALL(glGetProgramiv(shader_index, GL_INFO_LOG_LENGTH, &length));

				std::string message;
				message.resize(length);

				GL_CALL(glGetProgramInfoLog(shader_index, length, NULL, &message[0u]));

				GUI_EXCEPTION("Shader source code failed to link.\nMessage: " + message);
			}

			return shader_index;
		}

		static std::uint32_t get_uniform_location(std::string const& name, std::uint32_t shader_index)
		{
			std::uint32_t result;

			GL_CALL(result = glGetUniformLocation(shader_index, name.c_str()));
			GUI_ASSERT(result != -1, "Uniform with such name does not exist!\nName: " + name);

			return result;
		}


		static std::string read_file_content(std::string const& filepath)
		{
			auto file = std::fstream{ filepath, std::ios::in };

			if (!file)
			{
				file.close();
				GUI_EXCEPTION("Failed to open file: " + filepath);
			}

			auto content = std::string{};

			file.seekg(0, std::ios::end);
			content.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

			file.close();

			return content;
		}

		static std::uint32_t load_sub_shader(std::string const& filepath, shader_type type)
		{
			auto const content = read_file_content(filepath);
			auto const* const source = content.c_str();

			if (std::strlen(source) == 0)
				GUI_EXCEPTION("Shader source code failed to compile. File: " + filepath + "\nMessage: source code is empty");

			auto gl_index = std::uint32_t{};

			GL_CALL(gl_index = glCreateShader(type));

			GL_CALL(glShaderSource(gl_index, 1u, &source, NULL));
			GL_CALL(glCompileShader(gl_index));

			std::int32_t result;

			GL_CALL(glGetShaderiv(gl_index, GL_COMPILE_STATUS, &result));

			if (!result)
			{
				std::int32_t length;
				std::string message;
				GL_CALL(glGetShaderiv(gl_index, GL_INFO_LOG_LENGTH, &length));

				message.resize(length);
				GL_CALL(glGetShaderInfoLog(gl_index, length, nullptr, &message[0u]));

				GUI_EXCEPTION("Shader source code failed to compile. File: " + filepath + "\nMessage: " + message);
			}

			return gl_index;
		}
	}
}