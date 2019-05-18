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

const int width_window = 640;
const int height_window = 640;

class Vector3
{
public:
	union {
		struct { float x_, y_, z_; };
		float v_[3];
	};

	Vector3(const float& _x, const float& _y, const float& _z)
		: x_(_x), y_(_y), z_(_z)
	{}
};

//Vec3 colors[3] = { Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0) };
//Vec3 pos[3] = { Vec3(0.0, 0.0, 0.0), Vec3(1.0f, 0.0, 0.0), Vec3(0.0f, 1.0f, 0.0) };
//GLubyte indices[] = { 0, 1, 2 };

const int num_vertices = 24;
const int num_quads = 6;

const Vector3 colors[num_vertices] =
{
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),

	Vector3(1, 0, 0),
	Vector3(1, 0, 0),
	Vector3(1, 0, 0),
	Vector3(1, 0, 0),

	Vector3(0, 1, 0),
	Vector3(0, 1, 0),
	Vector3(0, 1, 0),
	Vector3(0, 1, 0),

	Vector3(1, 1, 0),
	Vector3(1, 1, 0),
	Vector3(1, 1, 0),
	Vector3(1, 1, 0),

	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),

	Vector3(1, 0, 1),
	Vector3(1, 0, 1),
	Vector3(1, 0, 1),
	Vector3(1, 0, 1)
};

Vector4<float> positions[num_vertices] =
{
	Vector4<float>(0.0, 0.0, 0.5, 1.0),  //마지막 1.0은 점을 뜻함.
	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.0, 0.0, 0.0, 1.0),

	Vector4<float>(0.0, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),
	Vector4<float>(0.0, 0.5, 0.5, 1.0),

	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),

	Vector4<float>(0.0, 0.0, 0.5, 1.0),
	Vector4<float>(0.0, 0.0, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.5, 1.0),

	Vector4<float>(0.0, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0),

	Vector4<float>(0.0, 0.5, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0)
};

const GLbyte indices[num_quads * 4] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	16, 17, 18, 19,
	20, 21, 22, 23
};

Matrix4<float> mat;

void moveBox()
{
	const float dx = 0.05;
	const float dy = 0.05;
	const float dz = 0.05;

	/*Matrix4<float> tr;
	tr.setRow(0, 1, 0, 0, dx);
	tr.setRow(1, 0, 1, 0, dx);
	tr.setRow(2, 0, 0, 1, dx);
	tr.setRow(3, 0, 0, 0, 1);
	*/

	const float theta = 1.0 / 360.0 * 1.0 * 3.141592;

	////rotation about z-axis
	//Matrix4<float> rot; // identity matrix 단위행렬
	//rot.setRow(0, cos(theta), -sin(theta), 0, 0);
	//rot.setRow(1, sin(theta), cos(theta), 0, 0);
	//rot.setRow(2, 0, 0, 1, 0);
	//rot.setRow(3, 0, 0, 0, 1);

	//Vector4<float> center(0.25, 0.25, 0.25, 1.0);
	////translate obj to origin
	//Matrix4<float> tr_to_o;
	//tr_to_o.setRow(0, 1, 0, 0, -0.25);
	//tr_to_o.setRow(1, 0, 1, 0, -0.25);
	//tr_to_o.setRow(2, 0, 0, 1, -0.25);
	//tr_to_o.setRow(3, 0, 0, 0, 1);

	//Matrix4<float> tr_invert;
	//tr_to_o.setRow(0, 1, 0, 0, 0.25);
	//tr_to_o.setRow(1, 0, 1, 0, 0.25);
	//tr_to_o.setRow(2, 0, 0, 1, 0.25);
	//tr_to_o.setRow(3, 0, 0, 0, 1);
	//
	//Matrix4<float> tempo;
	//tempo.multiply(rot.v_, tr_to_o.v_);
	//mat.multiply(tr_invert.v_, tempo.v_);
	Matrix4<float> tr;
	tr.setRow(0, 1, 0, 0, -0.25);
	tr.setRow(1, 0, 1, 0, -0.25);
	tr.setRow(2, 0, 0, 1, -0.25);
	tr.setRow(3, 0, 0, 0, 1);

	Matrix4<float> tr_inv;
	tr_inv.setRow(0, 1, 0, 0, 0.25);
	tr_inv.setRow(1, 0, 1, 0, 0.25);
	tr_inv.setRow(2, 0, 0, 1, 0.25);
	tr_inv.setRow(3, 0, 0, 0, 1);

	Matrix4<float> rot;
	rot.setRow(0, cos(theta), -sin(theta), 0, 0);
	rot.setRow(1, sin(theta), cos(theta), 0, 0);
	rot.setRow(2, 0, 0, 1, 0);
	rot.setRow(3, 0, 0, 0, 1);

	Matrix4<float> temp;
	temp.multiply(rot.v_, tr.v_);
	mat.multiply(tr_inv.v_, temp.v_);

	
	for (int v = 0; v < num_vertices; v++)
	{
		//positions[v].x_ += dx;
		//positions[v].y_ += dy;
		//positions[v].z_ += dz;
		Vector4<float> temp = positions[v];
		mat.multiply(temp, positions[v]);
	}
}

int main(void)
{
	//Vector4<float> point(0.0, 0.0, 0.0, 1.0); // 호모지니어스 쿠디네이츠
	//Vector4<float> vector(0.0, 0.0, 0.0, 0.0);

	//const float dx = 0.1;
	//const float dy = 0.2;
	//const float dz = 0.133;

	//point.x_ += dx;
	//point.y_ += dy;
	//point.z_ += dz;

	//Matrix4<float> mat;
	//mat.setRow(0, 1.0, 0.0, 0.0, 0.0);
	//mat.setRow(1, 0.0, 1.0, 0.0, 0.0);
	//mat.setRow(2, 0.0, 0.0, 1.0, 0.0);
	//mat.setRow(3, 0.0, 0.0, 0.0, 1.0);

	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
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
	//glOrtho(-0.2, 1.2, -0.2, 1.2, -10.0, 10.0);
	glOrtho(-1.2, 1.2, -1.2, 1.2, -100.0, 100.0);
	//TODO: consider anisotropic view
	gluLookAt(12, 3, 12, 0.0, 0.0, 0.0, 0, 1, 0);
	//glLoadIdentity();
	//gluLookAt(1, 1, 1, 0.5, 0.5, 0.5, 0, 1, 0);
	//gluLookAt(0, 0, 0, 0.25, 0.25, 0.25, 0, 1, 0);
	//glEnableVertexAttribArray(0);
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	GLuint vbo[3];
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//NOTE: don't forget glDeleteBuffersARB(1, &vbo);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		moveBox(); // animate objects  다보내줄필요는없고, 포지션정보만 gpu로 전송하면된다.
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		////traslate point from ( 0, 0, 0 ) to ( 1, 0, 0 )
		//point.x_ = 1.0;
		//point.y_ = 0.0;
		//point.z_ = 0.0;

		////traslate point by ( dx, dy, dz ) 
		//point.x_ += dx;
		//point.y_ += dy;
		//point.z_ += dz;


		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <- depth test

		//TODO: draw here
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(4, GL_FLOAT, 0, 0);		// Vector4

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, num_quads * 4, GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	glDeleteBuffersARB(3, vbo);

	glfwTerminate();

	return 0;
}

