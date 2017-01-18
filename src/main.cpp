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
#include "../headers/Shader.hpp"
#include "../headers/Camera.hpp"
#include "../headers/Box.hpp"
#include "../headers/Lamp.hpp"
#include "../headers/Skybox.hpp"
#include "../headers/Trunk.hpp"
#include "../headers/Gear.hpp"

#define GEAR_TEETH_NO 17
#define ANIMATION_SPEED 1.0f

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();


// Camera
Camera  camera(glm::vec3(0.0f, 0.5f, 6.0f));
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool	keys[1024];

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

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

	glm::vec3 lightPos(-5.2f, 5.0f, -5.0f);


	// Build and compile our shader program
	Shader lightingWithTexShader("shaders/lightingWithTex.vs", "shaders/lightingWithTex.frag");
	Shader lightingShader("shaders/lighting.vs", "shaders/lighting.frag");
	Shader lampShader("shaders/lamp.vs", "shaders/lamp.frag");
	Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.frag");

	Box island(20.0f, 0.05f, 20.0f);
	island.SetTexture("textures/grass-pattern.png");
	island.SetShader(&lightingWithTexShader);
	island.SetCamera(&camera);

	Box platform(3.0f, 0.4f, 5.0f);
	platform.SetTexture("textures/stone.png");
	platform.SetShader(&lightingWithTexShader);
	platform.SetCamera(&camera);

	Lamp lamp(1.5f, 1.5f, 1.5f);
	lamp.SetCamera(&camera);
	lamp.SetShader(&lampShader);

	Skybox skybox;
	skybox.SetCamera(&camera);
	skybox.SetShader(&skyboxShader);

	Trunk trunk(30);
	trunk.SetCamera(&camera);
	trunk.SetShader(&lightingWithTexShader);
	GLfloat displacement = 0.0f;
	GLfloat maxDisplacement = 0.5f;
	GLfloat displacementFactor = 0.01f;
	bool positiveDirection = true;

	Gear leftGear(GEAR_TEETH_NO);
	leftGear.SetCamera(&camera);
	leftGear.SetShader(&lightingShader);
	GLfloat leftGearRotationAngle = 0.0f;

	Gear rightGear(GEAR_TEETH_NO);
	rightGear.SetCamera(&camera);
	rightGear.SetShader(&lightingShader);
	GLfloat rightGearRotationAngle = 0.0f;

	GLfloat animationDirection = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model;

		island.Draw(lightPos, model);

		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		platform.Draw(lightPos, model);

		glm::mat4 leftGearModel = glm::mat4();
		glm::mat4 rightGearModel = glm::mat4();

		leftGearModel = glm::translate(leftGearModel, glm::vec3(-0.4f, 0.4f, 0.0f));
		rightGearModel = glm::translate(rightGearModel, glm::vec3(0.4f, 0.4f, 0.0f));

		leftGearModel = glm::rotate(leftGearModel, -3.14f/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		rightGearModel = glm::rotate(rightGearModel, -3.14f/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		animationDirection = positiveDirection ? 1.0f : -1.0f;

		leftGearRotationAngle += deltaTime * -animationDirection * ANIMATION_SPEED;
		leftGearModel = glm::rotate(leftGearModel, leftGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

		rightGearRotationAngle += deltaTime * animationDirection * ANIMATION_SPEED;
		rightGearModel = glm::rotate(rightGearModel, rightGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

		leftGear.Draw(lightPos, leftGearModel);
		rightGear.Draw(lightPos, rightGearModel);

		model = glm::mat4();
		if (positiveDirection)
			displacement += displacementFactor * ANIMATION_SPEED;
		else
			displacement -= displacementFactor * ANIMATION_SPEED;

		if (displacement > maxDisplacement)
			positiveDirection = false;

		if (displacement < -maxDisplacement)
			positiveDirection = true;

		model = glm::translate(model, glm::vec3(0.0f, 0.5f, displacement - 0.8f));

		trunk.Draw(lightPos, model);

		model = glm::mat4();
		lamp.Draw(lightPos, model);

		skybox.Draw();

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
