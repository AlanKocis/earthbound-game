#pragma once
class HealthBar
{
private:
	float* vertices;
	float percentHealth;
	unsigned int indices[6] = {
		0, 1, 3,
		3, 2, 0
	};
public:
	void create_vertices(int vertices_size, float verticesArr[]);
	unsigned int* get_indices();
	float* get_vertices();
	HealthBar();
	~HealthBar();
};