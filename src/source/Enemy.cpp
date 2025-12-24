#include "Enemy.hpp"

#include "myWindow.hpp"

#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/fwd.hpp>

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>


void Enemy::init()
{

    m_size     = glm::vec2(25, 100);
    m_Velocity = 0;
    m_Position = glm::vec2(0, (HEIGHT - m_size.y) / 2.f);

    float l_vertices[] = {
        0.0f,     0.0f,     // top-left
        m_size.x, 0.0f,     // top-right
        m_size.x, m_size.y, // bottom-right
        0.0f,     m_size.y  // bottom-left
    };

    unsigned int l_indicate[] = { 0, 1, 2,
                                  0, 2, 3 };

    m_Sh.init("../src/shader/shader.vert", "../src/shader/shader.frag");

    m_A.init();
    m_A.bind();

    m_B.init(l_vertices, sizeof(l_vertices));
    m_E.init(l_indicate, sizeof(l_indicate));

    m_A.setData(0, 2, 2, 0);

    m_A.unbind();
    m_B.unbind();
    m_E.unbind();
}

void Enemy::Ai(float p_dt,const glm::vec2& p_ballPos)
{
    if ((m_Position.y + m_size.y/2.f) > p_ballPos.y)
    {
        m_Velocity -= 5;
    }
    else
    {
        m_Velocity += 5;
    }

    m_Velocity = glm::clamp(m_Velocity,-100.f,100.f);

    m_Position.y += m_Velocity * p_dt;

    m_Position.y = glm::clamp( m_Position.y, 0.0f, HEIGHT - m_size.y );
}



void Enemy::Update(float p_dt,const glm::vec2& p_ballPos)
{
    m_Sh.doUseProgram();
    glm::mat4 Projection = glm::ortho(0.0f, WIDTH, // X
                                      HEIGHT, 0.0f, // Y
                                      -1.0f, 1.0f); // Z

    glm::mat4 Model = glm::translate(glm::mat4(1), glm::vec3(m_Position, 0.0f));

    unsigned int ProjLoc = glGetUniformLocation(m_Sh.getProgramID(), "Projection");
    unsigned int ModLoc  = glGetUniformLocation(m_Sh.getProgramID(), "Model");

    glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, glm::value_ptr(Projection));
    glUniformMatrix4fv(ModLoc, 1, GL_FALSE, glm::value_ptr(Model));

    m_Sh.unUseProgram();
}

void Enemy::Render()
{
    m_Sh.doUseProgram();
    m_A.bind();
    m_E.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_A.unbind();
    m_Sh.unUseProgram();
}

glm::vec2 Enemy::getPosition()
{
    return m_Position;
}

glm::vec2 Enemy::getSize()
{
    return m_size;
}

void Enemy::destory()
{
    m_Sh.unUseProgram();
    m_A.unbind();
    m_B.unbind();
    m_E.unbind();

    m_A.destory();
    m_B.destory();
    m_E.destory();
    m_Sh.destory();
}
