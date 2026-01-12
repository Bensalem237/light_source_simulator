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

        // Variables to hold the color of the light source
        float lightR = 1.0f;
        float lightG = 1.0f;
        float lightB = 1.0f;

        // Size of the light
        float haloSize = 800.0f;

        // Mouse position
        float mouseX = 0.0f;
        float mouseY = 0.0f;

        // Textures
        SDL_Texture* textureBackground = nullptr;
        // SDL_Texture* textureBulb = nullptr;
        SDL_Texture* textureHalo = nullptr;
};