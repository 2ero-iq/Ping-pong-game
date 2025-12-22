#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#define WIDTH  640.f
#define HEIGHT 480.f

class myWindow
{
public:
    void init();
    void Input(SDL_Event* p_event);
    void Render();
    void destory();

private:

    SDL_Window*   m_window;
    SDL_GLContext m_context;
};
