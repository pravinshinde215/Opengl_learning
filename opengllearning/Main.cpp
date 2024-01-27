#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>



/*
List of thing we need to look for ourself
1. what is glad ?
2. what does glfw does ?
*/
using namespace std;

int main()
{
	// first we inititalize it
	glfwInit();
	// giving the major and minor versio of opengl to glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OPEN GL profiles are just set of funtions for open gl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creating a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "opengl learning", NULL, NULL);


	// if glfw fails to create a window
	if (window == NULL)
	{
		cout << "something went wrong with the creating window";
		glfwTerminate();
		return -1;
	}

	// using the window we just created
	glfwMakeContextCurrent(window);

	// telling glad to load gl inside the context we just created
	gladLoadGL();

	// color changing of the window with open gl 
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	glViewport(0,0, 800,800);
	// just windows issue
	while (!glfwWindowShouldClose(window))
	{
		// once the window is created we process all the events such as resize and etc
		glfwPollEvents();
	}

	// delete the window after use
	glfwDestroyWindow(window);
	glfwTerminate();
	// then we terminate it
	return 0;
}