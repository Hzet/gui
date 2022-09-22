#pragma once
#include <memory>
#include <string>

namespace gui
{
	class application;

	extern std::unique_ptr<application> create_application();

	class application
	{
	public:
		void run();

		virtual void update();

	private:
		bool should_update() const;

	};
}