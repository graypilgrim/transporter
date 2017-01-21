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
#define ANIMATION_SPEED 2.0f

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

	glm::vec3 lightPos(-10.0f, 5.0f, -10.0f);
	glm::vec3 lightColor(2.0f, 2.0f, 2.0f);

	// Build and compile our shader program
	Shader lightingWithTexShader("shaders/lightingWithTex.vs", "shaders/lightingWithTex.frag");
	Shader lightingShader("shaders/lighting.vs", "shaders/lighting.frag");
	Shader lampShader("shaders/lamp.vs", "shaders/lamp.frag");
	Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.frag");

	Box island(20.0f, 0.05f, 20.0f);
	island.SetTexture("textures/grass-pattern.png");
	island.SetShader(&lightingWithTexShader);
	island.SetCamera(&camera);

	Box platform(2.5f, 0.4f, 4.0f);
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
	GLfloat maxDisplacement = 0.8f;
	GLfloat displacementFactor = 0.01f;
	bool positiveDirection = true;
	bool stopMoves = false;
	GLfloat stopTime = 0.0f;
	GLfloat waitingTime = 0.08f;

	Gear frontLeftGear(GEAR_TEETH_NO);
	frontLeftGear.SetCamera(&camera);
	frontLeftGear.SetShader(&lightingShader);
	GLfloat leftGearRotationAngle = 0.0f;

	Gear frontRightGear(GEAR_TEETH_NO);
	frontRightGear.SetCamera(&camera);
	frontRightGear.SetShader(&lightingShader);
	GLfloat rightGearRotationAngle = 0.0f;

	Gear backLeftGear(GEAR_TEETH_NO);
	backLeftGear.SetCamera(&camera);
	backLeftGear.SetShader(&lightingShader);

	Gear backRightGear(GEAR_TEETH_NO);
	backRightGear.SetCamera(&camera);
	backRightGear.SetShader(&lightingShader);

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

		island.Draw(lightPos, model, lightColor);

		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		platform.Draw(lightPos, model, lightColor);

		glm::mat4 frontLeftGearModel = glm::mat4();
		glm::mat4 frontRightGearModel = glm::mat4();
		glm::mat4 backLeftGearModel = glm::mat4();
		glm::mat4 backRightGearModel = glm::mat4();

		frontLeftGearModel = glm::translate(frontLeftGearModel, glm::vec3(-0.395f, 0.4f, 0.4f));
		frontRightGearModel = glm::translate(frontRightGearModel, glm::vec3(0.395f, 0.4f, 0.4f));
		backLeftGearModel = glm::translate(backLeftGearModel, glm::vec3(-0.395f, 0.4f, -0.4f));
		backRightGearModel = glm::translate(backRightGearModel, glm::vec3(0.395f, 0.4f, -0.4f));

		frontLeftGearModel = glm::rotate(frontLeftGearModel, (float)-M_PI/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		frontRightGearModel = glm::rotate(frontRightGearModel, (float)-M_PI/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		backLeftGearModel = glm::rotate(backLeftGearModel, (float)-M_PI/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		backRightGearModel = glm::rotate(backRightGearModel, (float)-M_PI/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		animationDirection = positiveDirection ? 1.0f : -1.0f;


		leftGearRotationAngle += stopMoves ? 0.0f : deltaTime * -animationDirection * ANIMATION_SPEED;
		frontLeftGearModel = glm::rotate(frontLeftGearModel, leftGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		backLeftGearModel = glm::rotate(backLeftGearModel, leftGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

		rightGearRotationAngle += stopMoves ? 0.0f : deltaTime * animationDirection * ANIMATION_SPEED;
		frontRightGearModel = glm::rotate(frontRightGearModel, rightGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		backRightGearModel = glm::rotate(backRightGearModel, rightGearRotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

		frontLeftGear.Draw(lightPos, frontLeftGearModel, lightColor);
		frontRightGear.Draw(lightPos, frontRightGearModel, lightColor);
		backLeftGear.Draw(lightPos, backLeftGearModel, lightColor);
		backRightGear.Draw(lightPos, backRightGearModel, lightColor);

		model = glm::mat4();
		if (positiveDirection)
			displacement += stopMoves ? 0.0f : displacementFactor * ANIMATION_SPEED;
		else
			displacement -= stopMoves ? 0.0f : displacementFactor * ANIMATION_SPEED;

		if (!stopMoves && displacement > maxDisplacement) {
			positiveDirection = false;
			stopMoves = true;
			stopTime = currentFrame;
		}

		if (!stopMoves && displacement < -maxDisplacement) {
			positiveDirection = true;
			stopMoves = true;
			stopTime = currentFrame;
		}

		if (currentFrame - stopTime > waitingTime)
			stopMoves = false;

		model = glm::translate(model, glm::vec3(0.0f, 0.5f, displacement - 1.0f));

		trunk.Draw(lightPos, model, lightColor);

		model = glm::mat4();
		// lamp.Draw(lightPos, model);

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
