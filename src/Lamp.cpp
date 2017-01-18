#include "../headers/Lamp.hpp"

Lamp::Lamp(GLfloat width, GLfloat height, GLfloat depth)
:Box(width, height, depth)
{}

void Lamp::Draw(glm::vec3 &lightPos, glm::mat4 &model) {
	shader->Use();

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera->Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, GetVerticesNo());
	glBindVertexArray(0);
}
