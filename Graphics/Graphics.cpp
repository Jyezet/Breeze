#pragma once
#include "Graphics.h"

bool Graphics::isClicked(Shape) {
    
}

Graphics::Window::Window(int width, int height, const char* title, int bgColor[3], void(*mainloop)(Window*), void(*init)(Window*)) {
    if (!glfwInit()) return;
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwSetCursorPosCallback(this->window, Graphics::cursorPosCB);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorEnterCallback(this->window, Graphics::cursorEnterCB);
    glfwSetMouseButtonCallback(this->window, Graphics::cursorClickCB);
    glfwSetScrollCallback(this->window, Graphics::scrollCB);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) return;

    glViewport((GLint) 0, (GLint) 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    init(this);

    GLclampf RED = (GLclampf) bgColor[0];
    GLclampf GREEN = (GLclampf) bgColor[1];
    GLclampf BLUE = (GLclampf) bgColor[2];

    glClearColor(RED, GREEN, BLUE, 1);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (Shape* shape : this->shapes) {
            shape->draw();
        }
        glfwGetFramebufferSize(this->window, &this->width, &this->height);
        
        mainloop(this);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Graphics::Window::~Window() {
    glfwTerminate();
}

Graphics::Shape::Shape(const char* name, float dimensions[], int mode, int numv, GLfloat colors[9]) {
    this->name = const_cast<char*>(name);
    this->mode = mode;
    this->numv = numv;
    this->visible = true;

    for (int i = 0; i < (numv * 3); i++) {
        this->dimensions[i] = dimensions[i];
    }

    for (int i = 0; i < 9; i++) {
        this->colors[i] = colors[i];
    }
}

void Graphics::Window::newShape(const char* name, float dimensions[], int mode, int numv, GLfloat colors[9]) {
    this->shapes.push_back(new Shape(name, dimensions, mode, numv, colors));
}

template <typename T>
void Graphics::remove(std::vector<T>& vec, size_t pos)
{
    vec.erase(vec.begin() + pos);
}

void Graphics::Window::delShape(const char* name) {
    for (size_t i = 0; i < this->shapes.size(); i++) {
        if (this->shapes[i]->name == name) {
            delete(this->shapes[i]);
            remove<Shape*>(this->shapes, i);
            break;
        }
    }
}

void Graphics::cursorClickCB(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        Graphics::mouse->clickxPos = (int) x;
        Graphics::mouse->clickxPos = (int) y;
    }
}

void Graphics::cursorEnterCB(GLFWwindow* window, int entered) {
    Graphics::mouse->cursorInWindow = (bool) entered;
}

void Graphics::scrollCB(GLFWwindow* window, double xOffset, double yOffset) {
    Graphics::mouse->scrollX = xOffset;
    Graphics::mouse->scrollY = yOffset;
}

void Graphics::Shape::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, this->dimensions);
    glColorPointer(3, GL_FLOAT, 0, this->colors);
    glDrawArrays(this->mode, 0, 4);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

static void Graphics::cursorPosCB(GLFWwindow* window, double xPos, double yPos) {
    Graphics::mouse->xPos = (int) xPos;
    Graphics::mouse->yPos = (int) yPos;
}

Graphics::Shape::~Shape() {
    // *Stuff about hiding the shape*
}