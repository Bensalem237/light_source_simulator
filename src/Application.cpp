#include <stb_image.h>
#include "application.h"

Application::Application() {
    Init();
}

Application::~Application() {
    Cleanup();
}

void Application::Init() {

    // 🔄️ Initialize SDL3 (Video only for now)
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error ❌ Init SDL : " << SDL_GetError << std::endl;
        return;
    }

    // 🪟 Create window
    window = SDL_CreateWindow ("Light Source Simulator 💡", 800, 600, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "Error ❌ Window Creation : " << SDL_GetError << std::endl;
        return;
    }

    // 🖌️ Create renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cerr << "Error ❌ Renderer Creation : " << SDL_GetError << std::endl;
        return;
    }

    isRunning = true;
    SDL_Log ("Application demmaree avec success ! 🎉");
}

void Application::run() {
    while (isRunning) {
        Update();
        Render();
    }
}

void Application::Update() {
    SDL_Event event;
    // 🔄️ Loop to manage all events (keyboard, mouse, closing)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false; // The window closes when we click the 'x'
        } 
    }
}

void Application::Render() {
    // 🎨 Choose the background color (R, G, B, Alpha)
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);

    // 🖌️ Clear the screen with the color
    SDL_RenderClear(renderer);

    // 🖼️ Present everything (Swap buffer)
    SDL_RenderPresent(renderer);
}

void Application::Cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Application closed successfully. 👋");
}

SDL_Texture* Application::LoadTexture(const char* filepath) {
    int width, height, channels;

    // Loads the image in RAM (raw pixels)
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);

    if (!data)
}