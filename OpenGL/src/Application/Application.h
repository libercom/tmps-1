#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utils/FileReader.h"

#include <iostream>
#include "../Core/Shader.h"
#include "../Factories/RectangleFactory.h"

#include "../../vendor/stb_image.h"

#include <glm/gtc/matrix_transform.hpp>

class Application
{
public:
    Application(Application& other) = delete;
    void operator=(const Application&) = delete;

    static Application* GetInstance();
    int Start();

private:
    static Application* m_Application;

    static glm::vec3 m_CameraPos;
    static glm::vec3 m_CameraFront;
    static glm::vec3 m_CameraUp;

    static float m_CameraSpeed;
    static float m_ScrollSpeed;

    Application() {}
    ~Application();
};
