#include "../headers/Trunk.hpp"

Trunk::Trunk(size_t segments)
:Object(12 * segments, 8), segmentsNo(segments) {
	vertices = new GLfloat[verticesNo * verticeCoordNo];

	memset(vertices, 0, GetArraySize());
	size_t index = 0;
	GLfloat zValue = 2.0f;
	CreateCircles(index, zValue);
	CreateSides(index, zValue);

	BindVertices();
	BindTexture();
}

Trunk::~Trunk() {
	delete[] vertices;
}


void Trunk::Draw(glm::vec3 &lightPos, glm::mat4 &model, glm::vec3 lightColor) {
	shader->Use();
	glUniform1i(glGetUniformLocation(shader->Program, "material.diffuse"), 0);
	glUniform3f(glGetUniformLocation(shader->Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), camera->Position.x, camera->Position.y, camera->Position.z);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glUniform3f(glGetUniformLocation(shader->Program, "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shader->Program, "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shader->Program, "light.specular"), 0.1f, 0.1f, 0.1f);

	glUniform3f(glGetUniformLocation(shader->Program, "material.specular"),  0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(shader->Program, "material.shininess"), 64.0f);


	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(camera->Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, GetTexture());

	glBindVertexArray(GetVAO());
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, GetVerticesNo());
	glBindVertexArray(0);
}


void Trunk::BindVertices() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, GetArraySize(), GetVertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, verticeCoordNo * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Trunk::BindTexture() {
    glGenTextures(1, &texture);
    int width, height;
    unsigned char* image;

    image = SOIL_load_image("textures/tree.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Trunk::CreateCircles(size_t &index, GLfloat height) {
	GLfloat zValue = 0.0f;
	CreateCircle(index, zValue);

	zValue = height;
	CreateCircle(index, zValue);
}

void Trunk::CreateCircle(size_t &index, GLfloat zValue) {
	GLfloat normal = zValue == 0.0f ? -1.0f : 1.0f;

	for (size_t i = 0; i < segmentsNo; ++i) {
		vertices[index] = 0.0f;
		vertices[index + 1] = 0.0f;
		vertices[index + 2] = zValue;
		vertices[index + 3] = 0.0f;
		vertices[index + 4] = 0.0f;
		vertices[index + 5] = normal;
		vertices[index + 6] = 0.5f;
		vertices[index + 7] = 0.8f;

		vertices[index + 8] = radius * cos(i * circleQuantum);
		vertices[index + 9] = radius * sin(i * circleQuantum);
		vertices[index + 10] = zValue;
		vertices[index + 11] = 0.0f;
		vertices[index + 12] = 0.0f;
		vertices[index + 13] = normal;
		vertices[index + 14] = 0.5f * cos(i * circleQuantum) + 0.5f;
		vertices[index + 15] = 0.20f * sin(i * circleQuantum) + 0.8f;

		vertices[index + 16] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 17] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 18] = zValue;
		vertices[index + 19] = 0.0f;
		vertices[index + 20] = 0.0f;
		vertices[index + 21] = normal;
		vertices[index + 22] = 0.5f * cos((i + 1) * circleQuantum) + 0.5f;
		vertices[index + 23] = 0.20f * sin((i + 1) * circleQuantum) + 0.8f;

		index += 24;
	}
}

void Trunk::CreateSides(size_t &index, GLfloat zValue) {
	GLfloat textureXQuantum = 1.0f / segmentsNo;

	for (size_t i = 0; i < segmentsNo; ++i) {
		vertices[index] = radius * cos(i * circleQuantum);
		vertices[index + 1] = radius * sin(i * circleQuantum);
		vertices[index + 2] = 0.0f;
		vertices[index + 3] = cos(i * circleQuantum);
		vertices[index + 4] = sin(i * circleQuantum);
		vertices[index + 5] = 0.0f;
		vertices[index + 6] = i * textureXQuantum;
		vertices[index + 7] = 0.0f;

		vertices[index + 8] = radius * cos(i * circleQuantum);
		vertices[index + 9] = radius * sin(i * circleQuantum);
		vertices[index + 10] = zValue;
		vertices[index + 11] = cos(i * circleQuantum);
		vertices[index + 12] = sin(i * circleQuantum);
		vertices[index + 13] = 0.0f;
		vertices[index + 14] = i * textureXQuantum;
		vertices[index + 15] = 0.6f;

		vertices[index + 16] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 17] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 18] = zValue;
		vertices[index + 19] = cos((i + 1) * circleQuantum);
		vertices[index + 20] = sin((i + 1) * circleQuantum);
		vertices[index + 21] = 0.0f;
		vertices[index + 22] = (i + 1) * textureXQuantum;
		vertices[index + 23] = 0.6f;

		vertices[index + 24] = radius * cos(i * circleQuantum);
		vertices[index + 25] = radius * sin(i * circleQuantum);
		vertices[index + 26] = 0.0f;
		vertices[index + 27] = cos(i * circleQuantum);
		vertices[index + 28] = sin(i * circleQuantum);
		vertices[index + 29] = 0.0f;
		vertices[index + 30] = i * textureXQuantum;
		vertices[index + 31] = 0.0f;

		vertices[index + 32] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 33] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 34] = 0.0f;
		vertices[index + 35] = cos((i + 1) * circleQuantum);
		vertices[index + 36] = sin((i + 1) * circleQuantum);
		vertices[index + 37] = 0.0f;
		vertices[index + 38] = (i + 1) * textureXQuantum;
		vertices[index + 39] = 0.0f;

		vertices[index + 40] = radius * cos((i + 1) * circleQuantum);
		vertices[index + 41] = radius * sin((i + 1) * circleQuantum);
		vertices[index + 42] = zValue;
		vertices[index + 43] = cos((i + 1) * circleQuantum);
		vertices[index + 44] = sin((i + 1) * circleQuantum);
		vertices[index + 45] = 0.0f;
		vertices[index + 46] = (i + 1) * textureXQuantum;
		vertices[index + 47] = 0.6f;

		index += 48;
	}
}
