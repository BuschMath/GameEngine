#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

public:
    Camera() :
        m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
        m_forward(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_right(glm::vec3(1.0f, 0.0f, 0.0f)),
        m_viewMatrix(glm::mat4(1.0f)),
        m_projectionMatrix(glm::mat4(1.0f))
    {
        updateViewMatrix();
    }

    void setPosition(const glm::vec3& position)
    {
        m_position = position;
        updateViewMatrix();
    }

    void setForward(const glm::vec3& forward)
    {
        m_forward = glm::normalize(forward);
        updateViewMatrix();
    }

    void setUp(const glm::vec3& up)
    {
        m_up = glm::normalize(up);
        updateViewMatrix();
    }

    void setRight(const glm::vec3& right)
    {
        m_right = glm::normalize(right);
        updateViewMatrix();
    }

    void setProjection(float fov, float aspectRatio, float nearClip, float farClip)
    {
        m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    }

    const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }

    float getFOV() { return 2.0f * atan(1.0f / m_projectionMatrix[1][1]) * 180.0f / glm::pi<float>(); }

private:
    void updateViewMatrix()
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
    }
};

#endif // !CAMERA_H
