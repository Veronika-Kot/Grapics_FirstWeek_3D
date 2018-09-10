#include "globalStuff.h"
#include "linmath.h" //quotes if you write it

#include <stdlib.h> //<> are system include
#include <stdio.h>
#include "cShaderManager.h" 
#include <iostream>
using namespace std;

//cShaderManager Ted; // Stack based variable
cShaderManager* pTheShaderManager; // "Heap" based variable; its a pointer (on Stuck) to Ted (in Heap)


static const struct myVertexType
{
	float x, y, z; //location
	float r, g, b; //color
};

//an array of 3 above structs, x, y, r, g, b; 0.f= 0.0f
myVertexType vertices[36] =
{   //   X      Y    Z    R   G     B
	//FISH 3D
	
	{  0.8f,  0.0f,  -0.15f, 0.4f, 0.4f, 1.f }, // tail front
	{  1.0f, -0.3f, -0.11f, 0.4f, 0.4f, 1.f },
	{  1.0f,  0.3f, -0.11f, 0.4f, 0.4f, 1.f },

	{  0.8f,  0.0f,  -0.15f, 0.4f, 0.4f, 1.f }, // tail top
	{  1.0f,  0.3f, -0.19f, 0.4f, 0.4f, 1.f },
	{  1.0f,  0.3f, -0.11f, 0.4f, 0.4f, 1.f },

	{  0.8f,  0.0f,  -0.15f, 0.4f, 0.4f, 1.f }, // tail bottom
	{  1.0f, -0.3f, -0.11f, 0.4f, 0.4f, 1.f },
	{  1.0f, -0.3f, -0.19f, 0.4f, 0.4f, 1.f },

	{  0.8f,  0.0f,  -0.15f, 0.4f, 0.4f, 1.f }, // tail back
	{  1.0f, -0.3f, -0.19f, 0.4f, 0.4f, 1.f },
	{  1.0f,  0.3f, -0.19f, 0.4f, 0.4f, 1.f },

	{ -0.6f,  0.0f, -0.15f, 1.f, 1.f, 0.f }, // head front
	{  0.0f, -0.6f, 0.f, 1.f, 1.f, 0.f },
	{  0.0f,  0.6f, 0.f, 1.f, 1.f, 0.f },

	{ -0.6f, -0.0f,  -0.15f, 0.93f, 0.87f, 0.51f }, // head top
	{  0.0f,  0.6f, -0.3f, 0.93f, 0.87f, 0.51f },
	{  0.0f,  0.6f,  0.f, 0.93f, 0.87f, 0.51f},

	{ -0.6f, -0.0f,  -0.15f, 0.84f, 0.77f, 0.22f }, // head botton
	{  0.0f, -0.6f, -0.3f, 0.84f, 0.77f, 0.22f },
	{  0.0f, -0.6f,  0.f, 0.84f, 0.77f, 0.22f },

	{ -0.6f, -0.0f, -0.15f, 1.f, 1.f, 0.f }, // head back
	{  0.0f,  0.6f, -0.3f, 1.f, 1.f, 0.f },
	{  0.0f, -0.6f, -0.3f, 1.f, 1.f, 0.f },

	{  0.0f, -0.6f, 0.f, 1.f, 1.f, 0.f }, // body front
	{  0.0f,  0.6f, 0.f, 1.f, 1.f, 0.f },
	{  0.8f,  0.0f, -0.15f, 1.f, 1.f, 0.f },

	{  0.0f,  0.6f,  0.f, 0.93f, 0.87f, 0.51f }, // body top
	{  0.0f,  0.6f, -0.3f, 0.93f, 0.87f, 0.51f },
	{  0.8f,  0.0f,  -0.15f, 0.93f, 0.87f, 0.51f},

	{  0.0f, -0.6f,  0.f, 0.84f, 0.77f, 0.22f }, // body botton
	{  0.0f, -0.6f, -0.3f, 0.84f, 0.77f, 0.22f },
	{  0.8f, 0.0f,  -0.15f, 0.84f, 0.77f, 0.22f },

	{  0.0f, -0.0f, -0.3f, 1.f, 1.f, 0.f }, // body back
	{  0.0f,  0.6f, -0.3f, 1.f, 1.f, 0.f },
	{  0.8f,  0.0f,  -0.15f, 1.f, 1.f, 0.f }

};


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	GLFWwindow* window; //creates window of app and free console


	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1000, 580, "Under water", NULL, NULL);
	//(W, H, title, ?, ?)

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	//At this point GLFM is happy and has moved to OpenGL

	//Create a shader manager
	pTheShaderManager = new cShaderManager();

	cShaderManager::cShader vertexShader; //:: sign of scope 
	cShaderManager::cShader fragmentShader;

	vertexShader.fileName = "vertex01.glsl";
	vertexShader.shaderType = cShaderManager::cShader::VERTEX_SHADER;

	fragmentShader.fileName = "fragment01.glsl";
	fragmentShader.shaderType = cShaderManager::cShader::FRAGMENT_SHADER;

	if (pTheShaderManager->createProgramFromFile("myShader",
		vertexShader,
		fragmentShader)) {

		cout << "Compiled shaders OK" << endl;

	}
	else {
		cout << "OHH No" << endl;
		cout << pTheShaderManager->getLastError()<< endl;
	}

	GLuint vertex_buffer, vertex_shader, fragment_shader;//, program; //unsigned int
	GLint mvp_location, vpos_location, vcol_location;

	// NOTE: OpenGL error checks have been omitted for brevity

	//Copy buffer to GPU 
	glGenBuffers(1, &vertex_buffer); //& - passing by refference, gives the address
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer); //gives to a new buffer a type permanetly(never change)
	//- "vertex buffer"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 


	//***BELOW IS OLD shader compiler 
	/*
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL); //place object in the screen
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); //gives the color to the object
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	//Those 2 shadders are actually a program which runs

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program); */

	GLuint program = pTheShaderManager->getIDFromFriendlyName("myShader");
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");


	//   X      Y    Z    R   G     B
	//{ -0.6f, -0.4f, 0.f, 1.f, 0.f, 0.f }, // vertex 0

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, //"vPosition"
							3, // vec3 (xyz) 
								GL_FLOAT,
								GL_FALSE, // Don't normilize
								sizeof(float) * 6, //after you find the first value vertex, where to 
												   // find the next vertex -> 6 floats away, 6 for xyz+rgb
								(void*)0); //start with 0 byte



	glEnableVertexAttribArray(vcol_location);



	glVertexAttribPointer(vcol_location, //cColor
								3,  //vec3 rgb
								GL_FLOAT, 
								GL_FALSE,
							sizeof(float) * 6, //changed from 5
							(void*)(sizeof(float) * 3)); //changed from 2 to 3

	//there is a program logic
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		mat4x4 m, p, mvp;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClearColor(0.53, 0.81, 0.92, 0.5);
		glClear(GL_COLOR_BUFFER_BIT); //clear the screen

		
		mat4x4_identity(m);

		//rotating around Z axis
		//mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_rotate_Y(m, m, (float)glfwGetTime());

		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //Draws whatever in the buffer 3 - vertises; 
		//Can draw a point, line etc. by gining a coordinates. 

		glfwSwapBuffers(window); //swap windows, so we don't see actual drawing happenin
		glfwPollEvents();
	}

	//DELETING STUFF

	delete pTheShaderManager;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
