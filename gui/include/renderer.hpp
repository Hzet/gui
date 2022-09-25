#pragma once

namespace gui
{
	namespace internal
	{
		enum draw_type;
		class vertex_array;
	}

	class renderer
	{
	public:
		void draw(internal::vertex_array const& v_array, internal::draw_type type) const;

	private:
	};
}