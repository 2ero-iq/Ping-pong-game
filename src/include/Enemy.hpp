#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "myEBO.hpp"
#include "myShader.hpp"
#include "myVAO.hpp"
#include "myVBO.hpp"
class Enemy
{
public:
    void init();
    void Ai(float p_dt,const glm::vec2& p_ballPos);
    void Update(float p_dt,const glm::vec2& p_ballPos);
    void Render();
    void destory();


    glm::vec2 getPosition();
    glm::vec2 getSize();
private:

    myShader m_Sh;
    myVBO    m_B;
    myVAO    m_A;
    myEBO    m_E;

    glm::vec2 m_Position;
    float m_Velocity;
    glm::vec2 m_size;
};
