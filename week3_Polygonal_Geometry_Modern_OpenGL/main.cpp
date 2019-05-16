#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include "Vector3D.h"

const int width_window = 640 * 2;
const int height_window = 480 * 2;

int main(void)
{
	GLFWwindow *window = nullptr;

	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(width_window, height_window, "Kiseop!!", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glClearColor(180.0 / 255.0, 95.0 / 255.0, 95.0 / 255, 1);

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	const float aspect_ratio = (float)width / height; // 1.66, 1.9
	glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, -1.0, 1.0);

	float first_vertex[3] = { 0.0,0.0,0.0 };
	
	Vector3D<float> color[3] = {
		Vector3D<float>(1.0,0.0,0.0),
		Vector3D<float>(0.0,1.0,0.0),
		Vector3D<float>(0.0,0.0,1.0)
	};

	Vector3D<float> vertex[3] = {
		Vector3D<float>(0.0,0.0,0.0),
		Vector3D<float>(0.5,0.0,0.0),
		Vector3D<float>(0.25,0.5,0.0)
	};

	printf("%s \n", glGetString(GL_VERSION));
	/* Loop until the user closes the window */
	int num_vertices = 3;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		/* Render here */
		glBegin(GL_TRIANGLES);
		for (int v = 0; v < num_vertices; v++)
		{
			glColor3fv(color[v].values_);
			glVertex3fv(vertex[v].values_);
		}
		glEnd();

		//glEnableClientState(GL_COLOR_ARRAY);
		//glEnableClientState(GL_VERTEX_ARRAY);

		//glColorPointer(3, GL_FLOAT, 0, color);
		//glVertexPointer(3, GL_FLOAT, 0, vertex);

		//glDrawArrays(GL_TRIANGLES, 0, 9);

		//glDisableClientState(GL_COLOR_ARRAY);
		//glDisableClientState(GL_VERTEX_ARRAY);


		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

