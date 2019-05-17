#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include "Vector3D.h"
#include <gl/GLU.h>
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
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	printf("%s \n", glGetString(GL_VERSION));

	glClearColor(180.0 / 255.0, 95.0 / 255.0, 95.0 / 255, 1);

	gluLookAt(0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0, 1, 0); //Ä«¸Þ¶ó!

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	const float aspect_ratio = (float)width / height; // 1.66, 1.9
	glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, -1.0, 1.0);

	float first_vertex[3] = { 0.0,0.0,0.0 };

	Vector3D<float> colors[4] = {
		Vector3D<float>(1.0,0.0,0.0),
		Vector3D<float>(0.0,1.0,0.0),
		Vector3D<float>(0.0,0.0,1.0),
		Vector3D<float>(1.0,0.0,0.0),
		//Vector3D<float>(0.0,1.0,0.0),
		//Vector3D<float>(0.0,0.0,1.0)
	};

	Vector3D<float> vertex[4] = {
		Vector3D<float>(0.0,0.0,0.0),
		Vector3D<float>(0.5,0.0,0.0),
		Vector3D<float>(0.25,0.5,0.0),
		//Vector3D<float>(0.25,0.5,0.0),
		//Vector3D<float>(0.5,0.0,0.0),
		Vector3D<float>(0.5,0.5,-0.5)
	};
	GLubyte indices[] = { 0,1,2 ,1,2,3 };
	int num_vertices = 6;

	GLuint vbo[3];
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * sizeof(Vector3D<float>), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * sizeof(Vector3D<float>), vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 6, indices, GL_STATIC_DRAW);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
	

		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

		//	glDrawArrays(GL_TRIANGLES, 0, 6 * 3);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

