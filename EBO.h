#pragma once
class EBO
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	EBO(const void* data, unsigned int size);
	~EBO();

	void Bind() const;
	void Unbind() const;

	inline unsigned int get_count() const { return m_Count; }
};