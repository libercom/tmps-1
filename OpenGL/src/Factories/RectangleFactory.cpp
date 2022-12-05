#include "RectangleFactory.h"
#include <GL/glew.h>
#include <cstdint>

Shape* RectangleFactory::CreateTexturedRectangle(Shader* shader, unsigned char* image, int width, int height)
{
	Shape* texturedRectangle = new Shape(shader, glm::vec3(0.5f, 0.5f, 0.5f));

	float vertices[] = {
		// positions             // texture coord
		-0.5f,  -0.5f,  -0.5f,   0.0f, 0.0f,  // bottom right front
		 0.5f,  -0.5f,  -0.5f,   1.0f, 0.0f,  // bottom left front
		 0.5f,   0.5f,  -0.5f,   1.0f, 1.0f,  // top right front
		 0.5f,   0.5f,  -0.5f,   1.0f, 1.0f,  // top left front
		-0.5f,   0.5f,  -0.5f,   0.0f, 1.0f,  // bottom left front
		-0.5f,  -0.5f,  -0.5f,   0.0f, 0.0f,  // top right front
	};

	texturedRectangle->GenerateBuffers(vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	uint32_t texture;
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	texturedRectangle->SetImage(image, width, height);

	return texturedRectangle;
}

Shape* RectangleFactory::CreateRectangle(Shader* shader)
{
	Shape* rectangle = new Shape(shader, glm::vec3(0.5f, 0.5f, 0.5f));

	float vertices[] = {
		// positions         
		 0.5f, -0.5f,  0.5f,  // bottom right front
		-0.5f, -0.5f,  0.5f,  // bottom left front
		 0.5f,  0.5f,  0.5f,  // top right front
		-0.5f,  0.5f,  0.5f,  // top left front
		-0.5f, -0.5f,  0.5f,  // bottom left front
		 0.5f,  0.5f,  0.5f,  // top right front
	};

	rectangle->GenerateBuffers(vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	return rectangle;
}
