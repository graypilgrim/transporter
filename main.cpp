#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.hpp"
#include "Camera.hpp"
#include "Box.hpp"
#include "Skybox.hpp"
#include "Trunk.hpp"
#include "Gear.hpp"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();


// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool	keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

struct CameraData
{
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
};

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


	// Build and compile our shader program
	Shader lightingWithTexShader("shaders/lightingWithTex.vs", "shaders/lightingWithTex.frag");
	Shader lightingShader("shaders/lighting.vs", "shaders/lighting.frag");
	Shader lampShader("shaders/lamp.vs", "shaders/lamp.frag");
	Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.frag");

	Box box(1.0f, 1.0f, 1.0f);
	Box lamp(0.5f, 0.5f, 0.5f);
	Skybox skybox;

	Trunk trunk(30);

	Gear leftGear(17);
	Gear rightGear(17);

	CameraData cameraData;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();
		glUniform3f(glGetUniformLocation(lightingShader.Program, "objectColor"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "lightColor"),  1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		cameraData.modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		cameraData.viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
		cameraData.projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(cameraData.viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(cameraData.projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw the container (using container's vertex attributes)
		glBindVertexArray(leftGear.GetVAO());
		glm::mat4 model;
		glUniformMatrix4fv(cameraData.modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, leftGear.GetVerticesNo());
		glBindVertexArray(0);


		lightingWithTexShader.Use();
		glUniform1i(glGetUniformLocation(lightingWithTexShader.Program, "material.diffuse"), 0);
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "light.ambient"),  0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
		// Set material properties
		glUniform3f(glGetUniformLocation(lightingWithTexShader.Program, "material.specular"),  0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingWithTexShader.Program, "material.shininess"), 64.0f);

		// Create camera transformations
		view = camera.GetViewMatrix();
		// Get the uniform locations
		cameraData.modelLoc = glGetUniformLocation(lightingWithTexShader.Program, "model");
		cameraData.viewLoc  = glGetUniformLocation(lightingWithTexShader.Program,  "view");
		cameraData.projLoc  = glGetUniformLocation(lightingWithTexShader.Program,  "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(cameraData.viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(cameraData.projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glBindTexture(GL_TEXTURE_2D, trunk.GetTexture());

		// Draw the container (using container's vertex attributes)
		glBindVertexArray(trunk.GetVAO());
		glUniformMatrix4fv(cameraData.modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, trunk.GetVerticesNo());
		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		cameraData.modelLoc = glGetUniformLocation(lampShader.Program, "model");
		cameraData.viewLoc  = glGetUniformLocation(lampShader.Program, "view");
		cameraData.projLoc  = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(cameraData.viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(cameraData.projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
		glUniformMatrix4fv(cameraData.modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lamp.GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, lamp.GetVerticesNo());
		glBindVertexArray(0);

		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skybox.GetVAO());
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetTexture());
		glDrawArrays(GL_TRIANGLES, 0, skybox.GetVerticesNo());
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
