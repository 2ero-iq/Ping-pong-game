#pragma once
#include "Enemy.hpp"
#include "Player.hpp"
#include "myEBO.hpp"
#include "myShader.hpp"
#include "myVAO.hpp"
#include "myVBO.hpp"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Ball
{
public:
    void init(Player* p_Player, Enemy* p_Enemy);
    void Update(float p_dt);
    void destory();

    glm::vec2 getPos();

private:
    void Movement(float p_dt);
    void Render();

    myShader m_Sh;
    myVBO    m_B;
    myVAO    m_A;
    myEBO    m_E;

    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    glm::vec2 m_size;

    Player* m_Player;
    Enemy*  m_Enemy;
};
