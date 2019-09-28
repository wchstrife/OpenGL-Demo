#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// 回调函数声明
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// 窗口的大小
const GLuint WIDTH = 800, HEIGHT = 600;

// 定义顶点着色器和片元着色器
const GLchar* vertexShaderSouce = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

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

	// 构建并编译着色器

	// 顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSouce, NULL);
	glCompileShader(vertexShader);
	// 检查是否编译成功
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 片段着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// 检查是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 连接着色器
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// 检查连接是否成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// 连接完成之后，要删除之前的着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 设置定点数组->放到缓存中->再输入顶点属性
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		 0.5f, -0.5f, 0.0f, // Right 
		 0.0f,  0.5f, 0.0f  // Top   
	};
	GLuint VBO;		// 定点缓冲对象
	GLuint VAO;		// 顶点数组对象
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 先绑定VAO->在绑定VBO，传入顶点数据->设置顶点属性指针
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// 复制顶点数组到缓冲中

	glVertexAttribPointer(0, 3,  GL_FLOAT,  GL_FALSE, 3 * sizeof(GLfloat),  (GLvoid*)0);	// 设置定点属性指针
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	// Tips:为了后面安全的解绑

	glBindVertexArray(0);	// 解绑VAO供以后使用


	// 渲染主循环
	while (!glfwWindowShouldClose(window))
	{
		// 检查是否有事件
		glfwPollEvents();

		// 渲染
		// 清除缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 画三角形
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// 画3个顶点
		glBindVertexArray(0);

		// 双缓冲区
		glfwSwapBuffers(window);
	}

	// 每次结束前调用清除相关数据
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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