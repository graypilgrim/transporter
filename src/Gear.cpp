#include "../headers/Gear.hpp"

Gear::Gear(size_t segments)
:Object(24 * segments, 6), segmentsNo(segments) {
	vertices = new GLfloat[verticesNo * verticeCoordNo];

	memset(vertices, 0, this->GetArraySize());
	size_t index = 0;
	GLfloat zValue = 0.2f;
	CreateCircles(index, zValue);
	CreateSides(index, zValue);

	BindVertices();
}

Gear::~Gear() {
	delete[] vertices;
}

void Gear::Draw(glm::vec3 &lightPos, glm::mat4 &model, glm::vec3 lightColor) {
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), camera->Position.x, camera->Position.y, camera->Position.z);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glUniform3f(glGetUniformLocation(shader->Program, "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shader->Program, "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shader->Program, "light.specular"), 1.0f, 1.0f, 1.0f);

	glUniform3f(glGetUniformLocation(shader->Program, "material.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(shader->Program, "material.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(shader->Program, "material.specular"), 0.774597f, 0.774597f, 0.5774597);
	glUniform1f(glGetUniformLocation(shader->Program, "material.shininess"), 76.6f);

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera->Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(GetVAO());
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, GetVerticesNo());
	glBindVertexArray(0);
}

void Gear::CreateCircles(size_t &index, GLfloat height) {
	GLfloat zValue = 0.0f;
	CreateCircle(index, zValue);
	zValue = height;
	CreateCircle(index, zValue);
}

void Gear::CreateCircle(size_t &index, GLfloat zValue) {
	GLfloat normal = zValue == 0.0f ? -1.0f : 1.0f;

	for (size_t i = 0; i < segmentsNo; ++i) {
		vertices[index] = 0.0f;
		vertices[index + 1] = 0.0f;
		vertices[index + 2] = zValue;
		vertices[index + 3] = 0.0f;
		vertices[index + 4] = 0.0f;
		vertices[index + 5] = normal;

		vertices[index + 6] = vertices[index + 18] = radius * cos(i * circleQuantum);
		vertices[index + 7] = vertices[index + 19] = radius * sin(i * circleQuantum);
		vertices[index + 8] = vertices[index + 20] = zValue;
		vertices[index + 9] = 0.0f;
		vertices[index + 10] = 0.0f;
		vertices[index + 11] = normal;
		vertices[index + 21] = 0.0f;
		vertices[index + 22] = 0.0f;
		vertices[index + 23] = normal;

		vertices[index + 12] = vertices[index + 24] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 13] = vertices[index + 25] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 14] = vertices[index + 26] = zValue;
		vertices[index + 15] = 0.0f;
		vertices[index + 16] = 0.0f;
		vertices[index + 17] = normal;
		vertices[index + 27] = 0.0f;
		vertices[index + 28] = 0.0f;
		vertices[index + 29] = normal;

		vertices[index + 30] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 31] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 32] = zValue;
		vertices[index + 33] = 0.0f;
		vertices[index + 34] = 0.0f;
		vertices[index + 35] = normal;

		index += 36;
	}
}

void Gear::CreateSides(size_t &index, GLfloat zValue) {
	for (size_t i = 0; i < segmentsNo; ++i) {
		vertices[index] = radius * cos(i * circleQuantum);
		vertices[index + 1] = radius * sin(i * circleQuantum);
		vertices[index + 2] = 0.0f;

		vertices[index + 6] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 7] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 8] = 0.0f;

		vertices[index + 12] = radius * cos(i * circleQuantum);
		vertices[index + 13] = radius * sin(i * circleQuantum);
		vertices[index + 14] = zValue;

		GLfloat U[3] = {vertices[index + 6] - vertices[index],
						vertices[index + 7] - vertices[index + 1],
						vertices[index + 8] - vertices[index + 2]};

		GLfloat V[3] = {vertices[index + 12] - vertices[index],
						vertices[index + 13] - vertices[index + 1],
						vertices[index + 14] - vertices[index + 2]};

		GLfloat normal[3];
		normal[0] = U[1] * V[2] - U[2] * V[1];
		normal[1] = U[2] * V[0] - U[0] * V[2];
		normal[2] = U[0] * V[1] - U[1] * V[0];

		vertices[index + 3] = vertices[index + 9] = vertices[index + 15] = normal[0];
		vertices[index + 4] = vertices[index + 10] = vertices[index + 16] = normal[1];
		vertices[index + 5] = vertices[index + 11] = vertices[index + 17] = normal[2];

		vertices[index + 18] = radius * cos(i * circleQuantum);
		vertices[index + 19] = radius * sin(i * circleQuantum);
		vertices[index + 20] = zValue;
		vertices[index + 21] = normal[0];
		vertices[index + 22] = normal[1];
		vertices[index + 23] = normal[2];

		vertices[index + 24] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 25] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 26] = zValue;
		vertices[index + 27] = normal[0];
		vertices[index + 28] = normal[1];
		vertices[index + 29] = normal[2];

		vertices[index + 30] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 31] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 32] = 0.0f;
		vertices[index + 33] = normal[0];
		vertices[index + 34] = normal[1];
		vertices[index + 35] = normal[2];


		vertices[index + 36] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 37] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 38] = 0.0f;

		vertices[index + 42] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 43] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 44] = 0.0f;

		vertices[index + 48] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 49] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 50] = zValue;

		U[0] = vertices[index + 42] - vertices[index + 36];
		U[1] = vertices[index + 43] - vertices[index + 37];
		U[2] = vertices[index + 44] - vertices[index + 38];

		V[0] = vertices[index + 48] - vertices[index + 36];
		V[1] = vertices[index + 49] - vertices[index + 37];
		V[2] = vertices[index + 50] - vertices[index + 38];

		normal[0] = U[1] * V[2] - U[2] * V[1];
		normal[1] = U[2] * V[0] - U[0] * V[2];
		normal[2] = U[0] * V[1] - U[1] * V[0];

		vertices[index + 39] = vertices[index + 45] = vertices[index + 51] = -normal[0];
		vertices[index + 40] = vertices[index + 46] = vertices[index + 52] = -normal[1];
		vertices[index + 41] = vertices[index + 47] = vertices[index + 53] = -normal[2];

		vertices[index + 54] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 55] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 56] = zValue;
		vertices[index + 57] = -normal[0];
		vertices[index + 58] = -normal[1];
		vertices[index + 59] = -normal[2];

		vertices[index + 60] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 61] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 62] = zValue;
		vertices[index + 63] = -normal[0];
		vertices[index + 64] = -normal[1];
		vertices[index + 65] = -normal[2];

		vertices[index + 66] = 1.5f * radius * cos(i * circleQuantum + circleQuantum/2);
		vertices[index + 67] = 1.5f * radius * sin(i * circleQuantum + circleQuantum/2);
		vertices[index + 68] = 0.0f;
		vertices[index + 69] = -normal[0];
		vertices[index + 70] = -normal[1];
		vertices[index + 71] = -normal[2];

		index += 72;
	}
}
