#pragma once

#include "Shader.h"

class Shape
{
public:
	Shape(Shader* shader, glm::vec3 position) : m_Shader(shader), m_Position(position) {};
	virtual ~Shape() { delete m_Vertices; };

	void Draw();
	void GenerateBuffers(float vertices[], size_t verticesNumber);
	void Bind();
	void SetImage(unsigned char* image, int width, int height);

	Shape* Clone();

	glm::vec3 m_Position;

protected:
	Shader* m_Shader;
	uint32_t m_VAO;
	uint32_t m_VBO;
	size_t m_VerticesNumber;
	float* m_Vertices;
	unsigned char* m_Image;
	int m_ImageWidth;
	int m_ImageHeight;
};