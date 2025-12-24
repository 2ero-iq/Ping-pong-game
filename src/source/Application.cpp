#include "Application.hpp"

#include "Enemy.hpp"
#include "Player.hpp"
#include "myWindow.hpp"

#include <glad/glad.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <spdlog/spdlog.h>


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
    myBall.init(&myPlayer, &myEnemy);

    is_running = true;
}

void Application::Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            is_running = false;

        if (e.type == SDL_EVENT_KEY_DOWN)
            if (e.key.scancode == SDL_SCANCODE_ESCAPE)
                is_running = false;

        myWindow::Input(&e);
    }

    myBall.Movement(1.f / 60.f);
    myPlayer.Input(1.f / 60.f);
    myEnemy.Ai(1.f / 60.f, myBall.getPos());
}

void Application::Update()
{

    int time2wait = MILLIESEC_PER_FRAME - (SDL_GetTicks() - millisecsLastFrame);
    if(time2wait > 0 &&  time2wait <= (int)MILLIESEC_PER_FRAME)
        SDL_Delay(time2wait);

    m_DT = (SDL_GetTicks() - millisecsLastFrame)/1000.f;

    // while (!(SDL_GetTicks() >= MILLIESEC_PER_FRAME + millisecsLastFrame))
    //     ;
    millisecsLastFrame = SDL_GetTicks();


    myEnemy.Update(m_DT, myBall.getPos());
    myBall.Update(m_DT);
    myPlayer.Update(m_DT);
}

void Application::Render()
{
    glClearColor(29 / 255.f, 32 / 255.f, 33 / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    myEnemy.Render();
    myBall.Render();
    myPlayer.Render();

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
        Update();
        Render();
    }
    destory();
}
