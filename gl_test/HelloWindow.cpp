#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// 回调函数声明
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800,  HEIGHT = 600;

int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// 初始化窗口
	glfwInit();
	// 设置窗口的参数
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 生成窗口，并绑定上下文
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// 在循环之前设置按键回调函数
	glfwSetKeyCallback(window, key_callback);

	// 使用GLEW的现代功能
	glewExperimental = GL_TRUE;
	// 初始化GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// 设置视口
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// 渲染主循环
	while (!glfwWindowShouldClose(window))
	{
		// 检查是否有事件
		glfwPollEvents();

		// 渲染
		// 清除缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 双缓冲区
		glfwSwapBuffers(window);
	}

	// 每次结束前调用清除相关数据
	glfwTerminate();
	return 0;
}

// 键盘的回调函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}