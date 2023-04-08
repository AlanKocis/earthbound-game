#include "HealthBar.h"

HealthBar::HealthBar()
	: percentHealth{ 1.0 } {
	vertices = nullptr;

}

float* HealthBar::get_vertices() {
	return vertices;
}

void HealthBar::create_vertices(int vertices_size, float verticesArr[]) {
		vertices = new float[vertices_size];
		for (int i = 0; i < vertices_size; i++) {
			*(vertices + i) = verticesArr[i];
		}
}

HealthBar::~HealthBar() {
	delete vertices;
}

unsigned int* HealthBar::get_indices() {
	return indices;
}
