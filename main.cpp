#include "renderer.h" // holds glad
#include <GLFW/glfw3.h>


#include "Shader.h"
#include "Hero.h"
#include "GameEngine.h"
#include "Enemy.h"

#include "stb_image.h"
#include <cmath>
#include <vector>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);
void takeDamage();
void gameStateCallBack(GLFWwindow* window);

GameEngine engine;
Hero player(25, 25);
bool menuIsOpen;
std::vector<Enemy*>enemies;

#define NEW_COMBAT 0
#define IN_COMBAT 1
#define WON_COMBAT 2
#define DEAD 3

#define PLAYER_TURN 0;
#define ENEMY_TURN 1;

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
//END boilerplate


	// callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	//Creating the player object

	float playerHealthBarVertices[] = {
	   -0.5f, -0.7f, 0.0f,		//bottom left
	   -0.5f, -0.6f, 0.0f,		//top left
		0.5f, -0.7f, 0.0f,		//bottom right
		0.5f, -0.6f, 0.0f		//top right
	};

	unsigned int playerHealthBarIndices[6] = {
		0, 1, 3,
		3, 2, 0
	};

	size_t phbVSize, phbISize;
	phbVSize = sizeof(playerHealthBarVertices) / sizeof(float);
	phbISize = sizeof(playerHealthBarIndices) / sizeof(unsigned int);
											//size                            //vertice array
	player.create_health_bar(phbVSize, playerHealthBarVertices, phbISize, playerHealthBarIndices);



	
	unsigned int playerHealthVBO, playerHealthVAO, playerHealthEBO;
	glGenVertexArrays(1, &playerHealthVAO);
	glGenBuffers(1, &playerHealthVBO);
	glGenBuffers(1, &playerHealthEBO);

	glBindVertexArray(playerHealthVAO);

	glBindBuffer(GL_ARRAY_BUFFER, playerHealthVBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), player.get_health_bar_vertices(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerHealthEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), player.get_health_bar_indices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);			//accesses whatever is bound by glBindVertexArray, glBindBuffer(GL_ARRAY_BUFFER,...) and glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ...)
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

// 
// Enemy objects and textures
//

	float enemy1Vertices[] = {
		//vertex				//texture
		 0.25f, 0.7f, 0.0f,		1.0f, 1.0f,			//top right
		 0.25f, -0.2f, 0.0f,		1.0f, 0.0f,			//bottom right
		-0.25f, -0.2f, 0.0f,		0.0f, 0.0f,			//bottom left
		-0.25f, 0.7f, 0.0f,		0.0f, 1.0f,			//top left
	};

	unsigned int enemyIndices[] = {
		0, 1, 3,
		1, 2, 3
	};


	unsigned int monsterVAO1, monsterVBO1, monsterEBO;
	glGenVertexArrays(1, &monsterVAO1);
	glGenBuffers(1, &monsterVBO1);
	glGenBuffers(1, &monsterEBO);
	
	glBindVertexArray(monsterVAO1);

	glBindBuffer(GL_ARRAY_BUFFER, monsterVBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(enemy1Vertices), enemy1Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, monsterEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(enemyIndices), enemyIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int monsterTex1;
	glGenTextures(1, &monsterTex1);
	glBindTexture(GL_TEXTURE_2D, monsterTex1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int imgW, imgH, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("starman.png", &imgW, &imgH, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgW, imgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	

// Shaders
	Shader healthBarShader("3.3.healthbarshader.vs", "3.3.healthbarshader.fs");
	int stopPosLocation = glGetUniformLocation(healthBarShader.ID, "stopPos");

	Shader starmanShader("3.3.enemy1shader.vs", "3.3.enemy1shader.fs");

	std::cout << player.get_health() << " " << player.get_max_health() << std::endl;
	std::cout << sizeof(player.get_health_bar_vertices()) << std::endl;
	std::cout << sizeof(float) * 12 << ' ' << sizeof(playerHealthBarVertices);

	float stopPosition;
	float percentHealth;















	while (!glfwWindowShouldClose(window)) {
		// process input
		processInput(window);
		gameStateCallBack(window);

		// background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// calculations necessary for rendering
		percentHealth = ((float)player.get_health() / player.get_max_health());
		stopPosition = -0.5f + (1.0f * percentHealth);

		// render player healthbar
		healthBarShader.use();
		glUniform1f(stopPosLocation, stopPosition);
		glBindVertexArray(playerHealthVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//render enemies
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, monsterTex1);
		starmanShader.use();
		glBindVertexArray(monsterVAO1);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		takeDamage();
	}



}

void takeDamage() {
	player.takeDMG();
}

void gameStateCallBack(GLFWwindow* window) {

	if (player.get_health() == 0) {
		engine.setGameState(DEAD);
	}

	if (engine.getGameState() == NEW_COMBAT) {
		for (int i = 0; i < engine.rollNumEnemies(); i++) {
			//enemies.push_back;
		}

		// roll textures for enemies
		engine.setGameState(IN_COMBAT);
	}
	else if (engine.getGameState() == IN_COMBAT) {

		// roll enemy action
	}
	else if (engine.getGameState() == WON_COMBAT) {
		// won combat - get rid of the enemy stuff - delete pointer to new etc
		// play animation?

	}
	else if (engine.getGameState() == DEAD) {
		//you died
		glfwSetWindowShouldClose(window, true);
	}
}