#include "Graphics/Graphics.cpp"
// This file should be automatically generated upon creating a new project
#include <Settings/PSettings.h>
// This file contains data about the engine
#include <Settings/BSettings.h>

using namespace Graphics;


void init(Window* window) {

}

// Location of all vertices (X, Y, Z; Always initialize Z to 0)
float vertices[9] = {
    0, 300, 0,
    300, 300, 0,
    300, 0, 0
};

// Colors in RGB
GLfloat color[9] = {
    255, 0, 0,
    0, 255, 0,
    0, 0, 255
};

void mainloop(Window* window) {
    // Create a triangle
    window->newShape("triangle", vertices, GL_TRIANGLES, 3, color);
    // If the cursor is inside the window, change the triangle's color
    if (mouse->cursorInWindow) {
        color[0] = 0;
        color[1] = 255;
        color[2] = 255;
    }
    else {
        color[0] = 255;
        color[1] = 0;
        color[2] = 0;
    }
}

int main()
{
    // Background color will be cyan
    int colors[3] = B_CYAN;
    // Create window
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, colors, &mainloop, &init);
    return 0;
}