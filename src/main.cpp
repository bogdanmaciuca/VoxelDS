#include "app.hpp"

class VoxelsDS : public App {
    bool Initialize() {
        return true;
    }

    void Release() {

    }

    void RenderFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void ProcessInput() {

    }
};

int main() {
    VoxelsDS app;
    return app.Run();
}

