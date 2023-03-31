#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

void Renderer::render(RenderComponent* component) {
    // Set the material properties
    Material* material = component->getMaterial();
    glUseProgram(material->getShaderProgram());
    glUniform3f(glGetUniformLocation(material->getShaderProgram(), "material.color"),
        material->getBaseColor().r, material->getBaseColor().g, material->getBaseColor().b);
    glUniform1f(glGetUniformLocation(material->getShaderProgram(), "material.shininess"),
        material->getShininess());

    // Set the model transformation matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), component->getPosition());
    modelMatrix = glm::rotate(modelMatrix, glm::radians(component->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(component->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(component->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, component->getScale());
    glUniformMatrix4fv(glGetUniformLocation(material->getShaderProgram(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);

    // Render the mesh
    Mesh* mesh = component->getMesh();
    glBindVertexArray(mesh->getVAO());
    glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
