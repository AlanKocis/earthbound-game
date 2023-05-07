#include "VAO.h"; 
#include "renderer.h"

VAO::VAO()
{
	glGenVertexArrays(1, &m_RendererID);
}

VAO::~VAO()
{
}

void VAO::addBuffer(const VBO& vb, GLint location, GLenum vecSize, GLsizei stride, unsigned int offset)
{
	vb.Bind();
	glVertexAttribPointer(location, vecSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(offset * sizeof(float)));

}

void VAO::addBuffers(const VBO& vb, const EBO& eb, GLint location, GLenum vecSize, GLsizei stride, unsigned int offset)
{
	vb.Bind();
	eb.Bind();
	glVertexAttribPointer(location, vecSize, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(offset * sizeof(float)));
}

void VAO::Bind()
{
	glBindVertexArray(m_RendererID);

}