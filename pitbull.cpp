#define SDL_MAIN_HANDLED 

using namespace std;

#include <SDL2/SDL.h>
#include <iostream>
#include "entt.hpp"

// message bus deps
#include <functional>
#include <queue>
#include <vector>

// texture dep
#include <SDL2/SDL_image.h>

#include "log.h"

#include "constants.h"
#include "window.h"
#include "texture.h"
#include "message.h"
#include "components.h"
#include "input.h"
#include "inputcodes.h"
#include "experimentalinput.h"

#define SCREEN_WIDTH     1280
#define SCREEN_HEIGHT    720

#define APP_TITLE "Game Engine Demo"

using namespace Engine;

/// <summary>
/// Global for general app control
/// </summary>
struct Controls {
    static void quit() { SDL_Quit(); }
    static void delay(int i) { SDL_Delay(i); }
};

/// <summary>
/// Global functions for interpreting Messages
/// </summary>
struct GameController {
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
   
    static void quit(Message message) {
        if (message.getValue() == QUIT) {
            exit(0);
        }
    }
    
    void input(Message message) {
        gvalue value = message.getValue();
        if (value == PUP) up = 1;
        if (value == PDOWN) down = 1;
        if (value == PLEFT) left = 1;
        if (value == PRIGHT) right = 1;
        if (value == RUP) up = 0;
        if (value == RDOWN) down = 0;
        if (value == RLEFT) left = 0;
        if (value == RRIGHT) right = 0;
    }
};





struct App {
    void run() {
        initialize();
        loop();
    }

    void quit() {
        Controls::quit();
    }

    ~App() {
        delete state;
        delete textureManager;
        delete messageBus;
        delete registry;
        delete renderer;
    }

private:
    Renderer* renderer;
    Window* window;
    Input* input;
    MessageBus* appBus;
    MessageBus* messageBus;
    TextureManager* textureManager;
    entt::registry* registry;
    GameController* state;

    void initialize() {
        registry = new entt::registry();
        window = new Window();
        renderer = new Renderer(*window);
        appBus = new MessageBus();
        messageBus = new MessageBus();
        input = new Input(messageBus);
        state = new GameController();

        textureManager = new TextureManager(*renderer, TEXTURE_NAMES);
        appBus->addReceiver([this](Message a) { state->quit(a); });
        messageBus->addReceiver([this](Message a) { state->input(a); });

        // Initializing the scene
        auto player = registry->create();
        registry->emplace<Position>(player, 100, 100);
        registry->emplace<Texture>(player, 0);
        registry->emplace<Velocity>(player, 4, 4);
        registry->emplace<Player>(player);




    }

    void loop() {
        while (1) {
            renderer->prepareScene();
            input->translate();

            auto a = registry->view<Position, Velocity, Player>();

            // Player agency system
            a.each([this](auto entity, Position& pos, Velocity& vel, Player p) {
                if (state->up) { pos.y -= vel.dy; }
                if (state->down) { pos.y += vel.dy; }
                if (state->left) { pos.x -= vel.dx; }
                if (state->right) { pos.x += vel.dx; }
            });

            textureManager->draw(*registry);
            renderer->presentScene();
            appBus->notify();
            messageBus->notify();
            Controls::delay(16);
        }
    }
};

App app;
void quit() {
    app.quit();
}


int main() {
    atexit(quit);
    app.run();
    return 0;
}