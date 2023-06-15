#include "input.h"

namespace Engine {

void Input::handleKeyDown(SDL_KeyboardEvent* event) {
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            messageBus->sendMessage(PUP);
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            messageBus->sendMessage(PDOWN);
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            messageBus->sendMessage(PLEFT);
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            messageBus->sendMessage(PRIGHT);
        }
    }
}
void Input::handleKeyUp(SDL_KeyboardEvent* event) {
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            messageBus->sendMessage(RUP);
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            messageBus->sendMessage(RDOWN);
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            messageBus->sendMessage(RLEFT);
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            messageBus->sendMessage(RRIGHT);
        }
    }
}

/*

TODO: Make it so that condition checks
only occur as needed to reduce responsibility 
in the game layer.

The funciton sig is: bool foo(SDL_Event* current, SDL_Event target)
*/
void Input::translate() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            messageBus->sendMessage(QUIT);
            break;
        case SDL_KEYDOWN:
            handleKeyDown(&event.key);
            break;
        default:
            handleKeyUp(&event.key);
            break;
        }
    }
}

Input::Input(MessageBus* m) {
    messageBus = m;
}


}