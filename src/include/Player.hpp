#pragma once
#include "myEBO.hpp"
#include "myShader.hpp"
#include "myVAO.hpp"
#include "myVBO.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Player
{
public:
    void init();
    void Input(float p_dt);
    void Update(float p_dt);
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
    float     m_Velocity;
    glm::vec2 m_size;
};
