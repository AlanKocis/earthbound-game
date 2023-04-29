#include "HealthBar.h"

HealthBar::HealthBar()
	: percentHealth{ 1.0 } {
	vertices = nullptr;
	indices = nullptr;
}

float* HealthBar::get_vertices() {
	return vertices;
}

unsigned int* HealthBar::get_indices() {
	return indices;
}


void HealthBar::create_vertices(size_t vertices_size, const float* verticesArr) {
		vertices = new float[vertices_size];
		for (size_t i = 0; i < vertices_size; i++) {
			*(vertices + i) = verticesArr[i];
		}
}

void HealthBar::create_indices(size_t indices_size, const unsigned int* indicesArr) {
	indices = new unsigned int[indices_size];
	for (size_t i = 0; i < indices_size; i++) {
		*(indices + i) = indicesArr[i];
	}
}

HealthBar::~HealthBar() {
	delete vertices;
	delete indices;
}

