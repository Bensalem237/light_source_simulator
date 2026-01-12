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
        SDL_Log ("Error ❌ Init SDL : %s", SDL_GetError());
        return;
    }

    // 🪟 Create window
    window = SDL_CreateWindow ("Light Source Simulator 💡", 800, 600, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        SDL_Log ("Error ❌ Window Creation %s: ", SDL_GetError());
        return;
    }

    // 🖌️ Create renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        SDL_Log ("Error ❌ Renderer Creation : %s", SDL_GetError());
        return;
    }

    // Load textures after the creation of the renderer
    textureBackground = LoadTexture("assets/images/Background.png");
    textureHalo = LoadTexture("assets/images/white_halo.png");
    // textureBulb = LoadTexture("assets/images/Bulb.png");

    // To avoid any crash if no image, we verify but continue
    if(!textureHalo) SDL_Log("Warning ‼️: Halo not found !");
    
    isRunning = true;
    SDL_Log ("Successfully launched application ! 🎉");
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
        } else if (event.type == SDL_EVENT_KEY_DOWN) {

            // R key -> Red
            if (event.key.key == SDLK_R) {
                lightR = 1.0f; lightG = 0.0f; lightB = 0.0f;
                SDL_Log("Red Light Selected ! 🔴");
            }

            // G key -> Green
            if (event.key.key == SDLK_G) {
                lightR = 0.0f; lightG = 1.0f; lightB = 0.0f;
                SDL_Log("Green Light Selected ! 🟢");
            }

            // B key -> Blue
            if (event.key.key == SDLK_B) {
                lightR = 0.0f; lightG = 0.0f; lightB = 1.0f;
                SDL_Log("Blue Light Selected ! 🔵");
            }

            // W key -> White
            if (event.key.key == SDLK_W) {
                lightR = 1.0f; lightG = 1.0f; lightB = 1.0f;
                SDL_Log("White Light Selected ! ⚪");
            }
        } else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            // event.wheel.y has value of +1 (up) or -1 (down)

            if (event.wheel.y > 0) {
                haloSize += 50.0f; // Increase size
            } else if (event.wheel.y < 0) {
                haloSize -= 50.0f; // Decrease size
            }

            // 🛡️ Security : Stop the light from becoming too small or negative
            if (haloSize < 100.0f) haloSize = 100.0f;
        }
    }

    // Update the position of the mouse
    SDL_GetMouseState(&mouseX, &mouseY);
}

void Application::Render() {
    // 🎨 Choose the background color (R, G, B, Alpha)
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);

    // 🖌️ Clear the screen with the color
    SDL_RenderClear(renderer);

    // --- Draw the images ---

    // The wall (Full screen)
    if (textureBackground) {
        // Modify the color of the background to dark
        SDL_SetTextureColorMod(textureBackground, 70, 70, 75);

        SDL_RenderTexture(renderer, textureBackground, nullptr, nullptr);
    }

    // The Halo (Centered)
    if (textureHalo) {
        // We define the color (red for testing)
        SDL_SetTextureColorModFloat(textureHalo, lightR, lightG, lightB); // Orange-red
        SDL_SetTextureAlphaModFloat(textureHalo, 1.0f); // Un peu transparent

        // We use mouseX and mouseY here!
        SDL_FRect rectHalo = {
            mouseX - (haloSize / 2),
            mouseY - (haloSize / 2),
            haloSize,
            haloSize
        };

        SDL_RenderTexture(renderer, textureHalo, nullptr, &rectHalo);
    }

    // The Bulb (In addition to the halo)
    /*if (textureBulb) {
        SDL_FRect rectBulb = { 400 - 50, 300 - 50, 100, 100}; // x, y, w, h
        SDL_RenderTexture(renderer, textureBulb, nullptr, &rectBulb);
    }*/

    // 🖼️ Present everything (Swap buffer)
    SDL_RenderPresent(renderer);
}

void Application::Cleanup() {
    SDL_DestroyTexture(textureBackground);
    SDL_DestroyTexture(textureHalo);
    // SDL_DestroyTexture(textureBulb);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Application closed successfully. 👋");
}

SDL_Texture* Application::LoadTexture(const char* filepath) {
    int width, height, channels;

    // 🧩 Loads the image in RAM (raw pixels)
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4); // 4 = Force RGBA

    if (!data) {
        SDL_Log("ERROR ❌ : Impossible to load the image %s", filepath);
        return nullptr;
    }

    // 🖼️ Creates the texture
    SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, data, width * 4);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // 🧹 Cleaning
    SDL_DestroySurface(surface);
    stbi_image_free(data);

    if (texture) {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_Log("SUCCESS 🎊 : Image loaded %s", filepath);
    } else {
        SDL_Log("ERROR ❌ : Failed to create texture %s", filepath);
    }

    return texture;
}