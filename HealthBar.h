#pragma once
class HealthBar
{
private:
	float* vertices;
	float percentHealth;
	unsigned int* indices;


public:
	void create_vertices(size_t vertices_size, const float* verticesArr);
	void create_indices(size_t indices_size, const unsigned int* indicesArr);
	unsigned int* get_indices();
	float* get_vertices();
	HealthBar();
	~HealthBar();
};