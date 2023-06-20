#include "renderer.h" // holds glad
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Hero.h"
#include "GameEngine.h"
#include "Enemy.h"

#include "stb_image.h"
#include <cmath>
#include <vector>s


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window);
void takeDamage();
void gameStateCallBack(GLFWwindow* window);
void freeEnemyArray();
void delay5sec();

GameEngine engine;
Hero player(25, 25);
bool menuIsOpen;


#define NEW_COMBAT 0
#define IN_COMBAT 1
#define WON_COMBAT 2
#define DEAD 3

#define PLAYER_TURN 0;
#define ENEMY_TURN 1;

int main() {

	*(engine.get_currMobs_head() + 0) = &player;

	engine.setGameState(NEW_COMBAT);












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



	unsigned int VAOs[3], VBOs[3];
	unsigned int monsterVAO1, monsterVBO1, monsterEBO;
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	glGenBuffers(1, &monsterEBO);
	
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		Hero* CurrMobPtr = *(engine.get_currMobs_head() + 1);

		//this thing now works lol!
		for (int i = 0; i < 3; i++)
		{
			if (CurrMobPtr != nullptr)
			{
				glBindVertexArray(VAOs[0]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			CurrMobPtr++;
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static Hero* currUserSelectEnemy;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		takeDamage();
		delay5sec();
		
	}


	if (player.get_myTurn() == true)
	{
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		{
			//need shader to periodically make the currently "selected" enemy glow over time.
			//selection should occur as follows: default as the middle 



		}

		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		{

		}
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
		std::cout << "Game state is now NEW COMBAT" << std::endl;

		/*static Enemy en1;
		Hero* enemyP;*/

		//freeEnemyArray();

		Hero* p = *(engine.get_currMobs_head() + 1);
		for (int i = 0; i < engine.rollNumEnemies(); i++) {
			//instead of pushing back enemies, we're gonna push back a pointer to an enemy
			//p = new Enemy;
		}
		player.set_myTurn(true);
		// roll textures for enemies
		engine.setGameState(IN_COMBAT);
	}
	else if (engine.getGameState() == IN_COMBAT) {
		std::cout << "Game state is now IN COMBAT" << std::endl;


		


		// turns will be calculated here
		// roll enemy action

		//i = enemies.begin();
		//if ()
		

	}
	else if (engine.getGameState() == WON_COMBAT) {
		std::cout << "Game state is now WON COMBAT" << std::endl;

		// won combat - get rid of the enemy stuff - delete pointer to new etc
		// play animation?

	}
	else if (engine.getGameState() == DEAD) {
		std::cout << "Game state is now DEAD" << std::endl;

		//you died
		glfwSetWindowShouldClose(window, true);
	}
}



//have a container with all the currently alive hero objects. maybe a pointer to hero obejct for polymorphism
//then CAN uhh do shit
//loop through the container and use it to select target for attack. Pass in the target to attack function as well.
//player always first in container 
//This can also be used to determine whose turn it is. Literally loop through and enemy attacks based off where a pointer is or something



//have to figure out multiple rendering.
//think i can use the same container from earlier!!!

//for right now only 3 enemies max... sad! and lame. but if not i will literally never finish this.


void freeEnemyArray()
{
	Hero** p = engine.get_currMobs_head();
	for (int i = 1; i < 4; i++)		// make SURE it doesn't delete [0] - thats the player.
	{
		if (p[i] != nullptr)
		{
			delete p[i];
		}
	}

}

void delay5sec()
{
	double t = glfwGetTime();
	for (int i = t; i < (t + 10000); i++)
	{
		std::cout << "Paused" << std::endl;
	}

}
