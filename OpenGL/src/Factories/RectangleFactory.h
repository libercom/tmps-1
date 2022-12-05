#pragma once

#include "../Core/Shape.h"

static class RectangleFactory
{
public:
	static Shape* CreateTexturedRectangle(Shader* shader, unsigned char* image, int width, int height);
	static Shape* CreateRectangle(Shader* shader);
private:

};