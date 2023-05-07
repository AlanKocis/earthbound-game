#pragma once
#include <string>
class Texture
{
private:
	static unsigned int ID;
	int width, height;
public:
	Texture(const std::string& filePath);
};

