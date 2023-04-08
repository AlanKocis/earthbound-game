#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Hero.h"

#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
// openGL boilerplate
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
//END boilerplate


	//Creating the player object

	Hero player(0, 25);
	float playerHealthBarVertices[] = {
	   -0.5f, -0.7f, 0.0f,		//bottom left
	   -0.5f, -0.6f, 0.0f,		//top left
		0.5f, -0.7f, 0.0f,		//bottom right
		0.5f, -0.6f, 0.0f		//top right
	};

	player.create_health_bar(sizeof(playerHealthBarVertices) / sizeof(float), playerHealthBarVertices);





	unsigned int playerHealthVBO, playerHealthVAO, playerHealthEBO;
	glGenVertexArrays(1, &playerHealthVAO);
	glGenBuffers(1, &playerHealthVBO);
	glGenBuffers(1, &playerHealthEBO);

	glBindVertexArray(playerHealthVAO);

	glBindBuffer(GL_ARRAY_BUFFER, playerHealthVBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), player.get_health_bar_vertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerHealthEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), player.get_health_bar_indices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Shaders
	Shader healthBarShader("3.3.healthbarshader.vs", "3.3.healthbarshader.fs");
	int stopPosLocation = glGetUniformLocation(healthBarShader.ID, "stopPos");

	std::cout << player.get_health() << " " << player.get_max_health();

	float stopPosition;
	float percentHealth;

	while (!glfwWindowShouldClose(window)) {
		// calculations necessary for rendering
		percentHealth = ((float)player.get_health() / player.get_max_health());
		stopPosition = -0.5f + (1.0f * percentHealth);

		// process input
		processInput(window);

		// color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render player healthbar
		healthBarShader.use();
		glUniform1f(stopPosLocation, stopPosition);
		glBindVertexArray(playerHealthVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		


		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}