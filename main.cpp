#include "renderer.h" // holds glad
#include <GLFW/glfw3.h>
#include "GameEngine.h"
#include "Shader.h"
#include "Hero.h"
#include "Enemy.h"
#include "Player.h"
#include "stb_image.h"
#include <cmath>
#include <vector>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);
void gameStateCallBack(GLFWwindow* window);


//-------------------------------------------------------------------------------------------------------------
	// global vars
GameEngine engine;
auto it = engine.getContainer().begin();
	// player object is in engine::turnContainer[0] now.
	

//-------------------------------------------------------------------------------------------------------------



int main() {

//-------------------------------------------------------------------------------------------------------------

	// window

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "earthbound", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

//-------------------------------------------------------------------------------------------------------------

	// callbacks

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

//-------------------------------------------------------------------------------------------------------------

	// here how this will work. Have a vector for the turn order. When it's your turn, switch a boolean that allows you to control which enemy to target.










	// Render loop
//---------------------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// process input
		processInput(window);

		//check turn state
		gameStateCallBack(window);

		// background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		





		
		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glfwTerminate();
	return 0;
}
//end main - real code begins here
//--------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}




}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static auto target = engine.getContainer().begin();
	
	if ((*it)->get_myTurn() == true)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
		{

		}
	}


}

void gameStateCallBack(GLFWwindow* window) {
	it = engine.getContainer().begin();
	// do a while(it->get_myTurn() == true) for the player to control, the hit method sets turn to false after



}

