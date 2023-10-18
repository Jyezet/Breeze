#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Settings/PSettings.h>
#include <vector>

#define B_RED {255, 0, 0}
#define B_GREEN {0, 255, 0}
#define B_BLUE {0, 0, 255}
#define B_YELLOW {255, 255, 0}
#define B_WHITE {255, 255, 255}
#define B_PINK {255, 0, 255}
#define B_CYAN {0, 255, 255}
#define B_BLACK {0, 0, 0}

namespace Graphics {
    struct Mouse {
        int clickxPos, clickyPos;
        int xPos, yPos;
        int scrollX, scrollY;
        bool cursorInWindow;
    };

    Mouse* mouse = new Mouse();

    class Shape {
    public:
        bool visible;
        float dimensions[12];
        char* name;
        float colors[9];
        float position[2];
        int mode;
        int numv;
        Shape(const char*, float[], int, int, GLfloat[9]);
        ~Shape();
        void draw();
    };

    class Window {
        GLFWwindow* window;
        std::vector<Shape*> shapes;
    public:
        int width, height;
        Window(int, int, const char*, int[3], void(*)(Window*), void(*)(Window*));
        ~Window();
        void newShape(const char*, float[], int, int, GLfloat[9]);
        void delShape(const char*);
    };

    template <typename T>
    void remove(std::vector<T>&, size_t);

    static void cursorPosCB(GLFWwindow*, double, double);
    void cursorEnterCB(GLFWwindow*, int);
    void cursorClickCB(GLFWwindow*, int, int, int);
    void scrollCB(GLFWwindow*, double, double);
    bool isClicked(Shape);
}