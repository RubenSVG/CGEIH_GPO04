#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 1800, HEIGHT = 1000;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 2.0f, 15.0f));//X, Y, Z
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float spotAngle = 0.0f;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

//Variables de animacion
bool anim = false;
bool tele = false;
bool animp1 = false;
bool animp2 = false;
bool animpC = false;
bool animm = false;
bool animv1 = false;
bool animv2 = false;
bool animv3 = false;
bool animsF = false;
bool animsT = false;
bool animsL = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = true;
bool recorrido4 = false;
bool recorrido5 = true;
bool recorrido6 = false;
float sillaF = 0.0f;
float sillaT = 0.0f;
float sillaL = 0.0f;
float puerta = 0.0f;
float puerta2 = 0.0f;
float puertaC = 0.0f;
float mecedora = 0.0f;
float v1 = 0.0f;
float v2 = 0.0f;
float v3 = 0.0f;
int bandera = 0;
int banderap2 = 0;
int banderapC = 0;
int banderame = 0;
int banderav1 = 0;
int banderav2 = 0;
int banderav3 = 0;

float vertices[] = {
	// positions        
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};




// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(-0.819f,1.116f,3.01f),
	glm::vec3(-2.415f,0.31f,0.762f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f)
};

glm::vec3 spotLightPositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
};

glm::vec3 Light1 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Light2 = glm::vec3(0.0f, 0.0f, 0.0f);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Iluminacion 2", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");


	Model Casa((char*)"Models/Casa/casacompleta.obj");
	Model Puerta1((char*)"Models/Casa/puerta1.obj");
	Model Puerta2((char*)"Models/Casa/puerta2.obj");
	Model Mecedora((char*)"Models/Casa/mecedora.obj");
	Model Ventana1((char*)"Models/Casa/ventana1.obj");
	Model Ventana2((char*)"Models/Casa/ventana2.obj");
	Model Ventana3((char*)"Models/Casa/ventana3.obj");
	Model SillaF((char*)"Models/Casa/sillaFrontal.obj");
	Model SillaT((char*)"Models/Casa/sillaTrasera.obj");
	Model SillaL((char*)"Models/Casa/sillaLateral.obj");
	Model PuertaCocina((char*)"Models/Casa/PuertaCocina.obj");


	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(0);


	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);//controla la iluminación
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);//aclara el escenario
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = Light1.x;
		lightColor.y = Light1.y;
		lightColor.z = Light1.z;


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.03f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.9f);



		// Point light 2
		glm::vec3 lightColor2;
		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = sin(glfwGetTime() * Light2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.03f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.5f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"),camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));




		glm::mat4 model(1);



		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.39f, 0.51f, 5.0f));
		model = glm::rotate(model, glm::radians(puerta), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta1.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.58f, 0.52f, -5.0));
		model = glm::rotate(model, glm::radians(puerta2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.9f));
		model = glm::rotate(model, glm::radians(mecedora), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mecedora.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.935f, 1.24f, 5.03f));
		model = glm::rotate(model, glm::radians(v1), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.06f, 1.24f, 5.03f));
		model = glm::rotate(model, glm::radians(v2), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.89f, 1.44f, -3.1f));
		model = glm::rotate(model, glm::radians(v3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana3.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.295f + sillaF, 0.2f, -2.931f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaF.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.782f + sillaT, 0.2f, -2.981f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaT.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.129, 0.2, -1.849 + sillaL));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaL.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.292f, 0.761f, -0.94f));
		model = glm::rotate(model, glm::radians(puertaC), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaCocina.Draw(lightingShader);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//model = glm::mat4(1);
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//// Draw the light object (using light's vertex attributes)
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(cubeVAO);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}


	if (animp1)
	{
		//if (keys[GLFW_KEY_1])
		//{
		if (puerta > -90.0f && bandera == 0) {
			puerta -= 1.0f;
			if (puerta == -90.0f) {
				bandera = 1;
			}
		}
		else if (puerta < 0.0f && bandera == 1) {
			puerta += 1.5f;
			if (puerta == 0.0f) {
				bandera = 0;
			}
		}

		//}

	}

	if (animp2) {
		if (puerta2 < 90.0f && banderap2 == 0) {
			puerta2 += 1.0f;
			if (puerta2 == 90.0f) {
				banderap2 = 1;
			}
		}
		else if (puerta2 > 0.0f && banderap2 == 1) {
			puerta2 -= 1.0f;
			if (puerta2 == 0.0f) {
				banderap2 = 0;
			}
			//}

		}
	}

	if (animm) {
		if (mecedora < 10.0f && banderame == 0) {
			mecedora += 1.0f;
			if (mecedora == 10.0f) {
				banderame = 1;
			}
		}
		else if (mecedora > -10.0f && banderame == 1) {
			mecedora -= 1.0f;
			if (mecedora == -10.0f) {
				banderame = 0;
			}
		}
	}

	if (animv3) {
		if (v3 > -90.0f && banderav3 == 0) {
			v3 -= 1.0f;
			if (v3 == -90.0f) {
				banderav3 = 1;
			}
		}
		else if (v3 < 0.0f && banderav3 == 1) {
			v3 += 1.0f;
			if (v3 == 0.0f) {
				banderav3 = 0;
			}
		}
	}

	if (animv1) {
		if (v1 > -90.0f && banderav1 == 0) {
			v1 -= 1.0f;
			if (v1 == -90.0f) {
				banderav1 = 1;
			}
		}
		else if (v1 < 0.0f && banderav1 == 1) {
			v1 += 1.0f;
			if (v1 == 0.0f) {
				banderav1 = 0;
			}
		}
	}

	if (animv2) {
		if (v2 > -90.0f && banderav2 == 0) {
			v2 -= 1.0f;
			if (v2 == -90.0f) {
				banderav2 = 1;
			}
		}
		else if (v2 < 0.0f && banderav2 == 1) {
			v2 += 1.0f;
			if (v2 == 0.0f) {
				banderav2 = 0;
			}
		}
	}


	if (anim) {
		Light1 = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	else if (!anim) {
		Light1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}


	if (tele == true) {
		Light2 = glm::vec3(0.0f, 0.0f, 1.0f);
	}
	else if (tele == false) {
		Light2 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	if (animsF)
	{
		if (recorrido1) {

			if (sillaF > 0.4f) {
				recorrido1 = false;
				recorrido2 = true;
			}
			else {
				sillaF += 0.01;

			}
		}
		if (recorrido2) {
			if (sillaF < -0.2f) {
				recorrido1 = true;
				recorrido2 = false;
			}
			else {
				sillaF -= 0.01;

			}
		}
	}

	if (animsT)
	{
		if (recorrido3) {

			if (sillaT < -0.4f) {
				recorrido3 = false;
				recorrido4 = true;
			}
			else {
				sillaT -= 0.01;

			}
		}
		if (recorrido4) {
			if (sillaT > 0.2f) {
				recorrido3 = true;
				recorrido4 = false;
			}
			else {
				sillaT += 0.01;

			}
		}
	}


	if (animsL)
	{
		if (recorrido5) {

			if (sillaL > 0.4f) {
				recorrido5 = false;
				recorrido6 = true;
			}
			else {
				sillaL += 0.01;

			}
		}
		if (recorrido6) {
			if (sillaL < -0.2f) {
				recorrido5 = true;
				recorrido6 = false;
			}
			else {
				sillaL -= 0.01;

			}
		}
	}



	if (animpC)
	{
		//if (keys[GLFW_KEY_1])
		//{
		if (puertaC > -90.0f && banderapC == 0) {
			puertaC -= 1.0f;
			if (puertaC == -90.0f) {
				banderapC = 1;
			}
		}
		else if (puertaC < 0.0f && banderapC == 1) {
			puertaC += 1.5f;
			if (puertaC == 0.0f) {
				banderapC = 0;
			}
		}

		//}

	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (!anim)
		{
			//
			anim = true;
		}
		else if(anim)
		{
			//Light1 = glm::vec3(0);
			anim = false;
		}
	}


	if (keys[GLFW_KEY_T])
	{
		if (tele==false)
		{
			//
			tele = true;
		}
		else if (tele == true)
		{
			//Light1 = glm::vec3(0);
			tele = false;
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (!animp1) {
			animp1 = true;
		}
		else if (animp1) {
			animp1 = false;
		}

	}

	if (keys[GLFW_KEY_2])
	{
		if (!animp2) {
			animp2 = true;
		}
		else if (animp2) {
			animp2 = false;
		}

	}

	if (keys[GLFW_KEY_3])
	{
		if (!animm) {
			animm = true;
		}
		else if (animm) {
			animm = false;
		}

	}

	if (keys[GLFW_KEY_4])
	{
		if (!animv1) {
			animv1 = true;
		}
		else if (animv1) {
			animv1 = false;
		}

	}

	if (keys[GLFW_KEY_5])
	{
		if (!animv2) {
			animv2 = true;
		}
		else if (animv2) {
			animv2 = false;
		}

	}

	if (keys[GLFW_KEY_6])
	{
		if (!animv3) {
			animv3 = true;
		}
		else if (animv3) {
			animv3 = false;
		}

	}


	if (keys[GLFW_KEY_7])
	{
		if (!animsF) {
			animsF = true;
		}
		else if (animsF) {
			animsF = false;
		}

	}

	if (keys[GLFW_KEY_8])
	{
		if (!animsT) {
			animsT = true;
		}
		else if (animsT) {
			animsT = false;
		}

	}

	if (keys[GLFW_KEY_9])
	{
		if (!animsL) {
			animsL = true;
		}
		else if (animsL) {
			animsL = false;
		}

	}


	if (keys[GLFW_KEY_0])
	{
		if (!animpC) {
			animpC = true;
		}
		else if (animpC) {
			animpC = false;
		}

	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}