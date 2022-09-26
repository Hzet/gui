/*																		*
 *----------------------------------------------------------------------*
 *------------------------------- gui ----------------------------------*
 *----------------------------------------------------------------------*
 * requirements:                                                        *
 *   - must support displaying of:                                      *
 *     > buttons:														*
 *       1. checkbox button                                             *
 *       2. radio button                                                *
 *		 3. button                                                      *
 *                                                                      *
 *     > textboxes                                                      *
 *     > labels                                                         *
 *     > plots                                                          *
 *                                                                      *
 *   - must provide a way to react on various actions:                  *
 *     > on click push                                                  *
 *     > on click release                                               *
 *     > on hover                                                       *
 *     > after click                                                    *
 *     > on focus                                                       *
 *                                                                      *
 *   - must provide a way to chain events in reaction to an event       *
 *     such as one of the above (most likely with lua script)           *
 *                                                                      *
 * how to use:                                                          *
 *                                                                      *
 *                                                                      *
 *   - objects can react to various UI events in form of actions        *
 *   that might be chained as well as it can communicate with each      *
 *   object within the same layer                                       *
 *                                                                      *
 *   - there is limited number of actions all of which could            *
 *   be modified to suit users needs                                    *
 *                                                                      *
 *   - graph and other data representing utilities can share it's data  *
 *   through a data_collection that can be access by all of the objects *
 *   in within one layer                                                *
 *                                                                      *
 *   - all of the standard events are handled automatically             *
 *                                                                      *
 *                                                                      *
 *                                                                      *
 *                                                                      *
 *----------------------------------------------------------------------*
 *------------------------------ build ---------------------------------*
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Overview:                                                           *
 *  - library uses opengl + glfw to render gui and glm for maths        *
 *                                                                      *
 *  - everything related to event handling, drawing and generally not   *
 *  necessary for user to have access to is contained in 'internal'     *
 *  sub-namespace                                                       *
 *                                                                      *
 *+ - application:                                                      *
 *+   > manages window display, triggers main program loop              *
 *+   > virtual base class, user can create an instance by defining     *
 *    create_window function                                            *
 *                                                                      *
 *+ - buffers:                                                          *
 *+   > index buffer                                                    *
 *+   > vertex buffer                                                   *
 *+   > vertex array                                                    *
 *                                                                      *
 *+ - renderer:                                                         *
 *+   > facility to provide a way to display graphic objects            *
 *    > a pointer to the renderer is embedded in graphic objects,       *
 *      so they can be drawn in place                                   *
 *                                                                      *
 *+ - shaders:                                                          *
 *+   > only basic shaders, with fixed amount                           *
 *      of uniforms are implemented                                     *
 *                                                                      *
 *  - shapes and figures:                                               *
 *    > rectangle                                                       *
 *    > circle                                                          *
 *    > point                                                           *
 *    > line                                                            *
 *    > lines                                                           *
 *    > triangle                                                        *
 *                                                                      *
 *  - input:                                                            *
 *    > input can be retrieved for any part of the code                 *
 *    > some, assumed default, events like e.g. ctrl+c are handled here *
 *                                                                      *
 *  - textures:                                                         *
 *    > every object has a place for texture                            *
 *    > textures are stored in the renderer while UI objects refer      *
 *    to them by index                                                  *
 *                                                                      *
 *  - UI:                                                               *
 *    > label                                                           *
 *    > button                                                          *
 *    > textbox                                                         *
 *    > checkbox                                                        *
 *    > radiobox                                                        *
 *    > list                                                            *
 *                                                                      *
 *  - layer:                                                            *
 *    > stores member gui objects and triggers events handling on them  *
 *    > can be switch between active, idle and invalid states           *
 *                                                                      *
 *  - actions:                                                          *
 *    > set of objects allowing user to chain actions after certain     *
 *    has occurred                                                      *
 *    > every UI object is allowed to have actions assigned             *
 *    to event occurrence                                               *
 *    > on hover                                                        *
 *    > on click                                                        *
 *                                                                      *
 *  - layer stack:                                                      *
 *    > acts like a stack, where top layer is currently active          *
 *    > preserves the state of other, inactive layers                   *
 *                                                                      *
 *                                                                      *
 *																		*/

#include <iostream>
#include "application.hpp"

namespace gui
{
	std::unique_ptr<application> create_application()
	{
		return std::make_unique<application>();
	}
}

int main()
{
	try
	{
		auto app = gui::create_application();

		app->run();

		app->close();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception raised: " << e.what() << std::endl;
	}
}