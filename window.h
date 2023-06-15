#pragma once
#include <SDL2/SDL.h>


namespace Engine {
	class Window {
	private:
		SDL_Window* handle;
	public:
		Window();
		~Window();
		SDL_Window* getHandle();
	};

	class Renderer {
	private:
		SDL_Renderer* handle;
	public:
		Renderer(Window& w);
		~Renderer();
		void prepareScene();
		void presentScene();
		SDL_Renderer* unwrap();
	};
}