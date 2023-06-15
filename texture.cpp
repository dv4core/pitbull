
#include "texture.h"
#include "log.h"

namespace Engine {
    TextureContainer::TextureContainer(Renderer& renderer, string path) {
        auto cPath = &path[0];
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", cPath);
        texture = IMG_LoadTexture(renderer.unwrap(), cPath);
        if (texture != NULL) {
            Log::write("Texture load successful.\n");
        }
        else {
            Log::error("Error loading texture.\n"); // TODO: Write a new error message for this one.
        }
    }
    SDL_Texture* TextureContainer::get() {
        return texture;
    }
    SDL_Texture* TextureContainer::unwrap() {
        return texture;
    }



    void TextureManager::blit(string textureName, int x, int y) const {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        TextureContainer container = containers[indices.at(textureName)];
        auto texture = container.get();
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer->unwrap(), texture, NULL, &dest);
    }


    TextureManager::TextureManager(Renderer& renderer, vector<string> names) {
        for (int i = 0; i < names.size(); i++) {
            auto name = names[i];
            containers.push_back(*new TextureContainer(renderer, toPath(name)));
            indices[name] = i;
        }
        this->renderer = &renderer;
    }

    int TextureManager::getIndex(string name) {
        return indices[name];
    }

    TextureContainer& TextureManager::getTexture(string name) {
        auto index = getIndex(name);
        return containers[index];
    }

    void TextureManager::draw(entt::registry& registry) {
        auto view = registry.view<Position, Texture>();
        for (auto [entity, pos, t] : view.each()) {
            auto x = pos.x;
            auto y = pos.y;
            blit(TEXTURE_NAMES[t.index], x, y);
        }
    }
}