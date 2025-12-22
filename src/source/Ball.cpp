#include "Ball.hpp"
#include "myWindow.hpp"


void Ball::init(Player* p_Player, Enemy* p_Enemy)
{

    m_Player = p_Player;
    m_Enemy = p_Enemy;

    srand(static_cast<unsigned int>(std::time(nullptr)));

    float angle = static_cast<float>(std::rand()) / RAND_MAX * glm::two_pi<float>();




    m_Velocity.x = 1;
    m_Velocity.y = std::sin(angle);

    float speed = 100;
    m_Velocity *= speed;

    SPDLOG_INFO("angle: {}",angle);
    SPDLOG_INFO("x: {}, y: {}",m_Velocity.x,m_Velocity.y);
    // m_Velocity.y = glm::sin(angleY);


    m_size = glm::vec2(10, 10);
    m_Position = glm::vec2((WIDTH-m_size.x)/2.f,(HEIGHT-m_size.y)/2.f);

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

void Ball::Movement(float p_dt)
{

    if(m_Position.y <= 0 || m_Position.y >= HEIGHT - m_size.y)
    {
        m_Velocity.y *= -1;
    }
    if (
        (
            (m_Position.y >= m_Player->getPosition().y &&
            m_Position.y <= m_Player->getPosition().y+m_Player->getSize().y)
            &&
            m_Position.x + m_size.x >= m_Player->getPosition().x
        )
        ||
        (
            (m_Position.y >= m_Enemy->getPosition().y &&
            m_Position.y <= m_Enemy->getPosition().y+m_Enemy->getSize().y)
            &&
            m_Position.x <= m_Enemy->getPosition().x + m_Enemy->getSize().x
        )
    )
    {
        m_Velocity.x *= -1;
    }

    m_Position += m_Velocity * p_dt;
}

void Ball::Render()
{
    m_Sh.doUseProgram();
    m_A.bind();
    m_E.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_A.unbind();
}


void Ball::Update(float p_dt)
{
    Movement(p_dt);

    m_Sh.doUseProgram();
    glm::mat4 Projection = glm::ortho(0.0f, WIDTH,  // X
                                      HEIGHT, 0.0f, // Y
                                      -1.0f, 1.0f); // Z

    glm::mat4 Model = glm::translate(glm::mat4(1), glm::vec3(m_Position,0.0f));

    unsigned int ProjLoc = glGetUniformLocation(m_Sh.getProgramID(),"Projection");
    unsigned int ModLoc = glGetUniformLocation(m_Sh.getProgramID(),"Model");

    glUniformMatrix4fv(ProjLoc,1,GL_FALSE,glm::value_ptr(Projection));
    glUniformMatrix4fv(ModLoc,1,GL_FALSE,glm::value_ptr(Model));


    Render();
    m_Sh.unUseProgram();
}

void Ball::destory()
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
