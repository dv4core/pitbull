#include "window.h"
#include "log.h"
#include "constants.h"
namespace Engine {
    Window::Window() {
        int windowFlags;
        windowFlags = 0;
        Log::error(SDL_Init(SDL_INIT_VIDEO) < 0, "Couldn't initialize SDL: %s\n", SDL_GetError());
        handle = SDL_CreateWindow(APP_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
        Log::error(!handle, "Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
    }
    Window::~Window() {
        SDL_DestroyWindow(handle);
    }

    SDL_Window* Window::getHandle() {
        return handle;
    }

    Renderer::Renderer(Window& w) {
        int rendererFlags;

        rendererFlags = SDL_RENDERER_ACCELERATED;

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        handle = SDL_CreateRenderer(w.getHandle(), -1, rendererFlags);
        Log::error(!handle, "Failed to create renderer: %s\n", SDL_GetError());
    }
    Renderer::~Renderer() {
        SDL_DestroyRenderer(handle);
    }
    void Renderer::prepareScene() {
        SDL_SetRenderDrawColor(handle, 96, 128, 255, 255);
        SDL_RenderClear(handle);
    }
    void Renderer::presentScene() {
        SDL_RenderPresent(handle);
    }

    SDL_Renderer* Renderer::unwrap() {
        return handle;
    }
}