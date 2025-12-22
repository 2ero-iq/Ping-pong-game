#pragma once
#include "Ball.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "myWindow.hpp"

#include <glad/glad.h>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

class Application
{
public:
    void run();

private:
    void init();
    void Input();
    void Render();
    void destory();


    bool  is_running    = false;
    float m_DT          = 1.0f / 60.0f;
    float m_accumulator = 0.0f;

    myWindow m_window;
    Player   myPlayer;
    Enemy    myEnemy;
    Ball     myBall;
};
