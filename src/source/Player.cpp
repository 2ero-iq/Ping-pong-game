#include "Player.hpp"

#include "myWindow.hpp"

#include <glad/glad.h>


void Player::init()
{

    m_size = glm::vec2(25, 100);
    m_Velocity = 200;
    m_Position = glm::vec2(WIDTH-m_size.x,(HEIGHT-m_size.y)/2.f);

    float l_vertices[] = {
        0.0f,     0.0f,     // top-left
        m_size.x, 0.0f,     // top-right
        m_size.x, m_size.y, // bottom-right
        0.0f,     m_size.y  // bottom-left
    };

    unsigned int l_indicate[] = {0, 1, 2, 0, 2, 3};

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

void Player::Input(float p_dt)
{
    const bool* key = SDL_GetKeyboardState(nullptr);

    if (key[SDL_SCANCODE_UP] && m_Position.y >= 0)
    {
        m_Position.y -= m_Velocity * p_dt;
    }

    else if (key[SDL_SCANCODE_DOWN] && m_Position.y <= HEIGHT-m_size.y)
    {
        m_Position.y += m_Velocity * p_dt;
    }
}



void Player::Update(float p_dt)
{
    m_Sh.doUseProgram();
    glm::mat4 Projection = glm::ortho(0.0f, WIDTH,  // X
                                      HEIGHT, 0.0f, // Y
                                      -1.0f, 1.0f); // Z

    glm::mat4 Model = glm::translate(glm::mat4(1), glm::vec3(m_Position,0.0f));

    unsigned int ProjLoc = glGetUniformLocation(m_Sh.getProgramID(),"Projection");
    unsigned int ModLoc = glGetUniformLocation(m_Sh.getProgramID(),"Model");

    glUniformMatrix4fv(ProjLoc,1,GL_FALSE,glm::value_ptr(Projection));
    glUniformMatrix4fv(ModLoc,1,GL_FALSE,glm::value_ptr(Model));

    m_Sh.unUseProgram();
}

void Player::Render()
{
    m_Sh.doUseProgram();
    m_A.bind();
    m_E.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_A.unbind();
    m_Sh.unUseProgram();
}

glm::vec2 Player::getPosition()
{
    return m_Position;
}

glm::vec2 Player::getSize()
{
    return m_size;
}

void Player::destory()
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
