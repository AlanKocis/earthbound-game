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
void key_callback(GLFWwindow*);

void processInput(GLFWwindow* window);
void gameStateCallBack(GLFWwindow* window);
std::vector<glm::mat4> get_enemy_transforms();

//-------------------------------------------------------------------------------------------------------------
	// global vars
GameEngine engine;
auto it = engine.getContainer().begin();
auto turn_it = engine.getContainer().begin();
	// player object is in engine::turnContainer[0] now.
auto target_it = engine.getContainer().begin();
int turnBuffer;

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

//-------------------------------------------------------------------------------------------------------------
//to-dos
	//TODO: line 179: turnBuffer needs to be incremented after xp gain when all enemies are hp==0
	//TODO: line 199: loop through and get the transforms

//-------------------------------------------------------------------------------------------------------------
// enemy vertices


	float en_Vertices[] = {
		0.5f,  1.0f, 0.0f,		1.0f, 1.0f,
		0.5f, -1.0f, 0.0f,		1.0f, 0.0f,
	   -0.5f, -1.0f, 0.0f,		0.0f, 0.0f,
	   -0.5f,  1.0f, 0.0f,		0.0f, 1.0f
	};

	unsigned int en_Indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int en_VAO, en_VBO, en_EBO;
	glGenVertexArrays(1, &en_VAO);
	glGenBuffers(1, &en_VBO);
	glGenBuffers(1, &en_EBO);
	glBindVertexArray(en_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, en_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(en_Vertices), en_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, en_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(en_Indices), en_Indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

//-------------------------------------------------------------------------------------------------------------
//texture


	unsigned int starman_Tex;
	glGenTextures(1, &starman_Tex);
	glBindTexture(GL_TEXTURE_2D, starman_Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, num_channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("starman.png", &width, &height, &num_channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to laod texture" << std::endl;
	}
	stbi_image_free(data);


//-------------------------------------------------------------------------------------------------------------
// shaders

	Shader en_shader("3.3.en_vertex_shader.glsl", "3.3.en_fragment_shader.glsl");

	en_shader.use();
	unsigned int target_uniform_location = glGetUniformLocation(en_shader.ID, "targeted");
	glUniform1i(target_uniform_location, 0);
	en_shader.setFloat("targeted", 0.0f);		//should be updated later in render loop with sin function to get red value.
	en_shader.setInt("ourTexture", 0);
	unsigned int transform_uniform_location = glGetUniformLocation(en_shader.ID, "transform");

//-------------------------------------------------------------------------------------------------------------
// Render loop
	while (!glfwWindowShouldClose(window)) {
		// process input
		processInput(window);
		key_callback(window);

		//check turn state
		gameStateCallBack(window);

		// background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto i = engine.getContainer().begin() + 1;	// + 1 to skip player objected
		//render enemies
		std::vector<glm::mat4> transforms = get_enemy_transforms();
		int t_i{};
		while (i != engine.getContainer().end())
		{

			// 
			
			//render each one with appropriate transformation matrix.
			// call get_enemy_transforms once per stage to return vector with appropriate transformation mat4 for each enemy.
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, starman_Tex);

			en_shader.use();

			//do sin thing for targeted enemy
			float red_amount = static_cast<float>(sin(glfwGetTime()));
			en_shader.setFloat("targeted", red_amount);
			//set transformation matrices
			glUniformMatrix4fv(transform_uniform_location, 1, GL_FALSE, glm::value_ptr(transforms.at(t_i)));
			glBindVertexArray(en_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



			i++;
			t_i++;
		}


		
		// glfw
		glfwSwapBuffers(window);
		glfwPollEvents();


		//
	}



	glfwTerminate();
	return 0;
}
//end main - real code begins here
//-------------------------------------------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//player can never be targeted here, watch out for that if it bugs out
void key_callback(GLFWwindow* window)
{
	
	if ((*target_it)->get_myTurn() == true)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
		{
			if (target_it > engine.getContainer().begin() + 1)	//+ 1 because first is player - cant be targeted
			{
				(*target_it)->targeted = false;
				it--;
				(*target_it)->targeted = true;
				
			}
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && engine.get_stage() != 1)
		{
			if (target_it < engine.getContainer().end() - 1) //-1 because .end() is past the final element - points to nothing.
			{
				(*target_it)->targeted = false;
				target_it++;
				(*target_it)->targeted = true;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && engine.get_stage() != 1)
		{
			// call attack() with the parameter as *it - this part is scary
			engine.getContainer()[0]->attack(*it);

		}

		
	}


}

void gameStateCallBack(GLFWwindow* window)
{
	if (engine.get_stage() == 0)	// stage gets ++d when initialize_stage is called
	{
		engine.initiate_stage(1);
		turnBuffer = 1;
		turn_it = engine.getContainer().begin();
	}
	else
	{
		if (engine.get_stage() < turnBuffer)		//turn buffer needs to be incremented after everything is dead and xp has been gained. 
		{											// i think for now it might work with just 1 turn? We'll see. Need to fix later.
			engine.initiate_stage(engine.get_stage());
		}
	}






	// it is what I want to control the turns.
	int max_turn = engine.getContainer().size();
	(*turn_it)->set_myTurn(true);
	if ((*turn_it)->get_myTurn() == false) { it++; }	//set turn to the next thing in stage container
	if (turn_it == engine.getContainer().end())
	{
		turn_it = engine.getContainer().begin();
		turnBuffer++;
	}
}

std::vector<glm::mat4> get_enemy_transforms()
{
	int enemy_count = engine.getContainer().size() - 1;		// - 1 b/c player in container too !! !
	std::vector<glm::mat4> transforms;

	// do a loop here later
	int negative_switch = 1;
	auto m_it = (engine.getContainer()).begin() + 1;
	while (m_it != (engine.getContainer()).end())
	{
		glm::mat4 translation = glm::mat4(1.0f);
		if (enemy_count == 1)
		{
			transforms.push_back(translation);
		}
		else if (enemy_count == 2)
		{
			translation = glm::translate(translation, glm::vec3(-0.35 * negative_switch, 0.0, 0.0));
			negative_switch *= -1;
			transforms.push_back(translation);
		}
		else if (enemy_count == 3)
		{
			if (it == engine.getContainer().begin() + 1) { transforms.push_back(translation); }
			else
			{
				translation = glm::translate(translation, glm::vec3(-0.5 * negative_switch, 0.0, 0.0));
				negative_switch *= -1;
			}
		}
		m_it++;
	}

	//i love c plusplus
	return transforms;

}