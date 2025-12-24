#pragma once
#include "Ball.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "myWindow.hpp"

#include <glad/glad.h>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

const Uint64 FPS = 60;
const Uint64 MILLIESEC_PER_FRAME = 1000/FPS;

class Application
{
public:
    void run();

private:
    void init();
    void Input();
    void Update();
    void Render();
    void destory();


    bool  is_running    = false;
    float m_DT          = 1.0f / 60.0f;

    // myWindow m_window;
    Player   myPlayer;
    Enemy    myEnemy;
    Ball     myBall;

    Uint64 millisecsLastFrame = 0;
};
