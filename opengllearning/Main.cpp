#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// source code for vertex and frament shaders
const char* vertexShaderSource = "#version 330 core\n" 
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(a.Pos.x, aPos.y, aPos.z, 1.0);\n"
"}\0"
;

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0"
;

/*
List of thing we need to look for ourself
1. what is glad ?
2. what does glfw does ?
3. what are vertex and fragment shaders in depth
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

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};
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

	glViewport(0,0, 800,800);

	// creating the shader
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	// once you create a shader you need to wrape it in something called shader programm
	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);


	// vertex buffer where you store all the vertacies pos
	GLuint VAO,VBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// just windows issue
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0, 3);
		glfwSwapBuffers(window);
		
		// once the window is created we process all the events such as resize and etc
		glfwPollEvents();
	}


	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderprogram);
	// delete the window after use
	glfwDestroyWindow(window);
	glfwTerminate();
	// then we terminate it
	return 0;
}