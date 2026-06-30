#include "app.hpp"
#include "log.hpp"

int App::Run() {
    InternalInitialize();
    if (!Initialize()) return 1;

    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();
        ProcessInput();

        RenderFrame();
        glfwSwapBuffers(mWindow);
    }

    Release();
    InternalRelease();
    return 0;
}

bool App::InternalInitialize() {
    if (!glfwInit()) {
        const char* error;
        glfwGetError(&error);
        Log::Error("Could not initialize GLFW: {}", error);
        return false;
    }

    mWindow = glfwCreateWindow(mWndWidth, mWndHeight, mWndTitle, nullptr, nullptr);
    if (!mWindow) {
        const char* error;
        glfwGetError(&error);
        Log::Error("Could not create GLFW window: {}", error);
        return false;
    }
    glfwMakeContextCurrent(mWindow);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return true;
}

void App::InternalRelease() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

