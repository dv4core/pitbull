#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entt.hpp"

#include "window.h"
#include "components.h"

#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

namespace Engine {

	const string ASSET_DIR = "./";
	const string TEXTURE_FMT = ".png";
	static string toPath(string name) {
		return ASSET_DIR + name + TEXTURE_FMT;
	};

	const vector<string> TEXTURE_NAMES = {
		"player"
	};

	class TextureContainer {
		SDL_Texture* texture;
	public:
		TextureContainer(Renderer& renderer, string path);
		SDL_Texture* get();
		SDL_Texture* unwrap();
	};

	class TextureManager {
		map<string, int> indices;
		vector<TextureContainer> containers;
		Renderer* renderer;
		void blit(string textureName, int x, int y) const;
	public:
		TextureManager(Renderer& renderer, vector<string> names);
		int getIndex(string name);
		TextureContainer& getTexture(string name);
		void draw(entt::registry& registry);
	};

}