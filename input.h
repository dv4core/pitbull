#pragma once
#include <SDL2/SDL.h>
#include "message.h"
#include <vector>
using std::vector;


namespace Engine {
	class Input {
	private:

		//vector<function<void(SDL_KeyboardEvent* e, SDL_KeyboardEvent target)>> checks;

		MessageBus* messageBus;
		void handleKeyDown(SDL_KeyboardEvent* event);
		void handleKeyUp(SDL_KeyboardEvent* event);
	public:
		void translate();
		Input(MessageBus* m);
	};
}
