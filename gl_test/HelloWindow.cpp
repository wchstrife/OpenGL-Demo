#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// �ص���������
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800,  HEIGHT = 600;

int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// ��ʼ������
	glfwInit();
	// ���ô��ڵĲ���
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// ���ɴ��ڣ�����������
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// ��ѭ��֮ǰ���ð����ص�����
	glfwSetKeyCallback(window, key_callback);

	// ʹ��GLEW���ִ�����
	glewExperimental = GL_TRUE;
	// ��ʼ��GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// �����ӿ�
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// ��Ⱦ��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ����Ƿ����¼�
		glfwPollEvents();

		// ��Ⱦ
		// �������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ˫������
		glfwSwapBuffers(window);
	}

	// ÿ�ν���ǰ��������������
	glfwTerminate();
	return 0;
}

// ���̵Ļص�����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}