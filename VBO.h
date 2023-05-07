#pragma once
class VBO 
{
private:
	unsigned int m_RendererID;
public:
	VBO(const void* data, unsigned int count);
	~VBO();

	void Bind() const;
	void Unbind() const;
};