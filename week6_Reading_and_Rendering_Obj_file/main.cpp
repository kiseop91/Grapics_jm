/*
	Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
	for Introduction to Computer Graphics, 2017 Spring
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include "Matrix4.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Vector3.h"
#include "ObjReader.h"

const int width_window = 640;
const int height_window = 640;
//
//const int num_vertices = 24;
//const int num_quads = 6;
//
//const Vector3<float> colors[num_vertices] =
//{
//	Vector3<float>(0, 0, 0.8),
//	Vector3<float>(0, 0, 0.8),
//	Vector3<float>(0, 0, 0.8),
//	Vector3<float>(0, 0, 0.8),
//
//	Vector3<float>(1, 0, 0),
//	Vector3<float>(1, 0, 0),
//	Vector3<float>(1, 0, 0),
//	Vector3<float>(1, 0, 0),
//
//	Vector3<float>(0, 1, 0),
//	Vector3<float>(0, 1, 0),
//	Vector3<float>(0, 1, 0),
//	Vector3<float>(0, 1, 0),
//
//	Vector3<float>(1, 1, 0),
//	Vector3<float>(1, 1, 0),
//	Vector3<float>(1, 1, 0),
//	Vector3<float>(1, 1, 0),
//
//	Vector3<float>(0.2, 0.2, 1),
//	Vector3<float>(0.2, 0.2, 1),
//	Vector3<float>(0.2, 0.2, 1),
//	Vector3<float>(0.2, 0.2, 1),
//
//	Vector3<float>(1, 0, 1),
//	Vector3<float>(1, 0, 1),
//	Vector3<float>(1, 0, 1),
//	Vector3<float>(1, 0, 1)
//};
//
//Vector3<float> positions[num_vertices] =
//{
//	Vector3<float>(0.0, 0.0, 0.5),
//	Vector3<float>(0.5, 0.0, 0.5),
//	Vector3<float>(0.5, 0.0, 0.0),
//	Vector3<float>(0.0, 0.0, 0.0),
//
//	Vector3<float>(0.0, 0.0, 0.5),
//	Vector3<float>(0.5, 0.0, 0.5),
//	Vector3<float>(0.5, 0.5, 0.5),
//	Vector3<float>(0.0, 0.5, 0.5),
//
//	Vector3<float>(0.5, 0.0, 0.5),
//	Vector3<float>(0.5, 0.0, 0.0),
//	Vector3<float>(0.5, 0.5, 0.0),
//	Vector3<float>(0.5, 0.5, 0.5),
//
//	Vector3<float>(0.0, 0.0, 0.5),
//	Vector3<float>(0.0, 0.0, 0.0),
//	Vector3<float>(0.0, 0.5, 0.0),
//	Vector3<float>(0.0, 0.5, 0.5),
//
//	Vector3<float>(0.0, 0.0, 0.0),
//	Vector3<float>(0.5, 0.0, 0.0),
//	Vector3<float>(0.5, 0.5, 0.0),
//	Vector3<float>(0.0, 0.5, 0.0),
//
//	Vector3<float>(0.0, 0.5, 0.5),
//	Vector3<float>(0.5, 0.5, 0.5),
//	Vector3<float>(0.5, 0.5, 0.0),
//	Vector3<float>(0.0, 0.5, 0.0)
//};
//
//const unsigned int indices[num_quads * 4] = {
//	0, 1, 2, 3,
//	4, 5, 6, 7,
//	8, 9, 10, 11,
//	12, 13, 14, 15,
//	16, 17, 18, 19,
//	20, 21, 22, 23
//};

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit()) return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// callbacks here

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(1, 1, 1, 1); // while background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(-1.2, 1.2, -1.2, 1.2, -100.0, 100.0);
	glOrtho(-1.2, 1.2, -1.2, 1.2, -100.0, 100.0);
	gluLookAt(1.0, 0, 1.0, 0.5, 0.5, 0.5, -0.2, 0.5, 1.5);
	//gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 0);

	// read 3D model from obj file
	OBJReader obj_reader;
	obj_reader.readObj("IronMan_Full_smooth.obj");
	//obj_reader.readObj("../../test-result-sphere_f80.obj");
	//obj_reader.dump();

	obj_reader.scaleToUnitBox();

	const std::vector < Vector3<float> > &vertices = obj_reader.pos_stack_;
	const std::vector < Vector3<unsigned int> >&indices = obj_reader.ix_stack_;

	// copy geometry to buffer object
	GLuint vbo[3];
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3<float>) * vertices.size()
		, &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3<float>) * vertices.size()
		, &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3<unsigned int>) * indices.size()
		, &indices[0], GL_STATIC_DRAW);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <- depth test

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);		// Vector 3

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//glDeleteBuffersARB(3, vbo);

	glfwTerminate();

	return 0;
}

