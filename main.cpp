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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);
void gameStateCallBack(GLFWwindow* window);
std::vector<glm::mat4> get_enemy_transforms();

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


		

		// render loop
		auto i = engine.getContainer().begin() + 1;
		while (i != engine.getContainer().end())
		{
			//render each one with appropriate transformation matrix.
			// call get_enemy_transforms to return vector with appropriate transformation mat4 for each enemy.
		}


		
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

//player can never be targeted here, watch out for that if it bugs out
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static auto target = engine.getContainer().begin() + 1;
	
	if ((*it)->get_myTurn() == true)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
		{
			if (target > engine.getContainer().begin() + 1)	//+ 1 because first is player - cant be targeted
			{
				(*it)->targeted = false;
				it--;
				(*it)->targeted = true;
				
			}
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
		{
			if (target < engine.getContainer().end() - 1) //-1 because .end() is past the final element - points to nothing.
			{
				(*it)->targeted = false;
				it++;
				(*it)->targeted = true;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{

		}

	}


}

void gameStateCallBack(GLFWwindow* window)
{
	it = engine.getContainer().begin();
	// do a while(it->get_myTurn() == true) for the player to control, the hit method sets turn to false after



}

std::vector<glm::mat4> get_enemy_transforms()
{
	std::vector<glm::mat4> transforms;

	int enemy_count = engine.getContainer().size() - 1;		// - 1 to account for player in container

	return transforms;

}