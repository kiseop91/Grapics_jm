#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"

const int width_window = 640 * 2;
const int height_window = 480 * 2;
float circle_center_x = 0.0;
float circle_center_y = 0.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		std::cout << "키가 입력되었습니다..!!!" << std::endl;

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		std::cout << "오른쪽으로 이동..!!!" << std::endl;
		circle_center_x -= 0.05;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		std::cout << "왼쪽으로 이동..!!!" << std::endl;
		circle_center_x += 0.05;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "x :" << xpos << "   y: " << ypos << std::endl;
}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context         mointor, share */
	window = glfwCreateWindow(width_window, height_window, "Kiseop!!", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here  etc) keyboard, mouse
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(80.0 / 255.0, 95.0 / 255.0, 95.0 / 255, 1); // while background
	//default color for display buffer 

	int width, height;
	//FrameBuffer는 화면에 그려질 화면 전체에 대한 정보를 담는 공간, 메모리입니다.
	//해상도라고 아시죠 ? 1024 * 768 또는 800 * 480 등등... 그 해상도에 그려질 화면에 대한 정보를 담습니다.
	glfwGetFramebufferSize(window, &width, &height); //프레임버퍼사이즈, 
	glViewport(0, 0, width, height);

	//your fame buffer is two dimensional array  x, y
	//your fame buffer is three dimensional array x, y, d

	//glOrtho(-1, 1, -1, 1, -1.0, 1.0);
	const float aspect_ratio = (float)width / height; // 1.66, 1.9
	glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, -1.0, 1.0);  //왼쪽 오른쪽 아래 위. 종횡비를맞춰주는함수


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT); // 컬러프레임버퍼, 현대그래픽시스템은 많은 프레임버퍼를 가지고있다.
									  // 참고할것 , double buffering에대해 공부해보기.

		//TODO: draw here  glBegin에 들어가는 인자는 검색해서알아보자.
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 0.0, 0.0);
		//glVertex3f(0.0, 0.0, 0.0); // == glVertex2f(0.0 , 0.0); in 2D drawing
		//glVertex3f(0.5, 0.0, 0.0);
		//glVertex3f(0.25, 0.5, 0.0);
		glVertex2f(circle_center_x, circle_center_y);

		const int num_triangles = 20;
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
		const float radius = 0.5;

		float theta = 0.0;
		for (int i = 0; i <= num_triangles; i++, theta += dtheta)
		{
			const float x = radius * cos(theta) + circle_center_x;
			const float y = radius * sin(theta) + circle_center_y;

			glVertex2f(x, y);
		}

		glEnd(); // this is an old-style OpenGL.

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

