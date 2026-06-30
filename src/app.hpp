#pragma once

class App {
public:
    virtual bool Initialize()   = 0;
    virtual void Release()      = 0;
    virtual void RenderFrame()  = 0;
    virtual void ProcessInput() = 0;

    // Returns 0 on success
    int Run();
protected:
    int mWndWidth = 1024;
    int mWndHeight = 768;
    const char* mWndTitle = "OpenGL App";

    GLFWwindow* mWindow;
private:
    bool InternalInitialize();
    void InternalRelease();
};

