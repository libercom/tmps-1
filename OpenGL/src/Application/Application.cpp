#include "Application.h"

Application* Application::GetInstance()
{
	if (m_Application != nullptr)
	{
		m_Application = new Application();
	}

	return m_Application;
}

int Application::Start()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1200, 800, "Libercom", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	auto processResize = [](GLFWwindow* w, int width, int height)
	{
		glViewport(0, 0, width, height);
	};

	auto processScroll = [](GLFWwindow* w, double xoffset, double yoffset)
	{
		if (yoffset == 1)
			m_CameraPos += m_ScrollSpeed * m_CameraFront;
		if (yoffset == -1)
			m_CameraPos -= m_ScrollSpeed * m_CameraFront;
	};

	auto processInput = [](GLFWwindow* w)
	{
		if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(w, true);

		if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
			m_CameraPos += m_CameraSpeed * m_CameraUp;

		if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
			m_CameraPos -= m_CameraSpeed * m_CameraUp;

		if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
			m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;

		if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
			m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
	};

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, processResize);
	glfwSetScrollCallback(window, processScroll);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("./src/Textures/itachi.jpg", &width, &height, &nrChannels, 0);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error occured the initializing glew\n";
	}

	Shader shader("./src/Shaders/vertex/vertex.glsl", "./src/Shaders/fragment/fragment.glsl");
	RectangleFactory rectangleFactory;

	Shape* rect1 = rectangleFactory.CreateTexturedRectangle(&shader, data, width, height);
	Shape* rect2 = rect1->Clone();

	rect2->m_Position = glm::vec3(2.5f, 2.5f, 2.5f);

	stbi_image_free(data);

	glEnable(GL_DEPTH_TEST);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Input processing */
		processInput(window);

		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
			100.0f);

		glm::mat4 view;
		view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		{
			rect1->Bind();

			glm::mat4 model = glm::mat4(1.0f);
			glm::translate(model, rect1->m_Position);

			shader.SetMat4("model", model);
			rect1->Draw();
		}

		{
			rect2->Bind();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, rect2->m_Position);

			shader.SetMat4("model", model);
			rect2->Draw();

		}

		//glm::translate(model, rect2->m_Position);
		//shader.SetMat4("model", model);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

Application::~Application()
{
	delete m_Application;
}

Application* Application::m_Application = nullptr;

glm::vec3 Application::m_CameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 Application::m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Application::m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float Application::m_CameraSpeed = 0.02f;
float Application::m_ScrollSpeed = 1.5f;
