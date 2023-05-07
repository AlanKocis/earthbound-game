#pragma once
#include "VBO.h"
#include "EBO.h"
class VAO
{
private:
	unsigned int m_RendererID;

public:
	VAO();
	~VAO();

	void addBuffer(const VBO& vb, GLint location, GLenum vecSize, GLsizei stride, unsigned int offset);
	void addBuffers(const VBO& vb, const EBO& eb, GLint location, GLenum vecSize, GLsizei stride, unsigned int offset);
	void Bind();
};