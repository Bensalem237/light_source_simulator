
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <windows.h> // To use SetConsoleOutputCP(65001)
#include "Application.h"

int main(int argc, char** argv) {
    SetConsoleOutputCP(65001); // Sets console to UTF-8 mode (to use emojis)
    Application app; // Create the object
    app.run(); // Run the loop
    return 0;
}