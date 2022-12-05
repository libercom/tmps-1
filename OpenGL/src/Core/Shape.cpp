#include "Shape.h"
#include <GL/glew.h>
#include <iostream>

void Shape::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, m_VerticesNumber);
}

void Shape::GenerateBuffers(float vertices[], size_t verticesNumber)
{
	m_VerticesNumber = verticesNumber;

	m_Vertices = new float[verticesNumber];

	memcpy(m_Vertices, vertices, verticesNumber);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesNumber, vertices, GL_STATIC_DRAW);
}

void Shape::Bind()
{
	glBindVertexArray(m_VAO);
}

void Shape::SetImage(unsigned char* image, int width, int height)
{
	m_Image = image;
	m_ImageWidth = width;
	m_ImageHeight = height;
}

Shape* Shape::Clone()
{
	Shape* shape = new Shape(m_Shader, m_Position);

	shape->GenerateBuffers(m_Vertices, m_VerticesNumber);

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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ImageWidth, m_ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Image);
	glGenerateMipmap(GL_TEXTURE_2D);

	return shape;
}
