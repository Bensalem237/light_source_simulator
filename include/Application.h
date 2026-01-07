#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class Application {
    public:
        Application(); // 🔨 Constructor
        ~Application(); // ⛏️ Destructor

        void run(); // 🧩 Runs the application

    private:
        void Init(); // ⚙️ Initialise SDL3
        void Update(); // 🔄️ Update logic
        void Render(); // 🖌️ Draw on screen
        void Cleanup(); // 🧹 Clear the memory

        // 🖼️ Load an image
        SDL_Texture* LoadTexture(const char* filepath);

        SDL_Window* window = nullptr; // 🪟 SDL window
        SDL_Renderer* renderer = nullptr; // 🖌️ Renderer
        bool isRunning = false;

        // Textures
        SDL_Texture* textureBackground = nullptr;
        SDL_Texture* textureBulb = nullptr;
        SDL_Texture* textureHalo = nullptr;
};