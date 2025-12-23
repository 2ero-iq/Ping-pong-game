#include "Application.hpp"

#include "Enemy.hpp"
#include "Player.hpp"
#include "myWindow.hpp"

#include <glad/glad.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>


void Application::init()
{

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SPDLOG_ERROR("COULD NOT INIT SDL");
    }

    myWindow::init();

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SPDLOG_ERROR("COULD NOT INIT GLAD");
    }

    myPlayer.init();
    myEnemy.init();
    myBall.init(&myPlayer,&myEnemy);

    is_running = true;
}

void Application::Input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            is_running = false;

        if(e.type == SDL_EVENT_KEY_DOWN)
            if(e.key.scancode == SDL_SCANCODE_ESCAPE)
                is_running = false;

        myWindow::Input(&e);
    }
}

void Application::Render()
{
    glClearColor(29 / 255.f, 32 / 255.f, 33 / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    myEnemy.Update(1.f / 60.f,myBall.getPos());
    myBall.Update(1.f / 60.f);
    myPlayer.Update(1.f / 60.f);

    myWindow::Render();
}

void Application::destory()
{
    myPlayer.destory();
    myEnemy.destory();
    myBall.destory();
    myWindow::destory();
    SDL_Quit();
}


void Application::run()
{
    init();
    while (is_running)
    {
        Input();
        Render();
    }
    destory();
}
