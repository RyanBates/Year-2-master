#include "Geometry.h"
#include "gl_core_4_4.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
using namespace glm;

Geometry::Geometry()
	:m_cam(nullptr),
	m_dir(false) {};

Geometry::~Geometry()
{
}

void Geometry::generateShader()
{
	// create shader
	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 Position; \
							layout(location=1) in vec4 Colour; \
							out vec4 vColour; \
							uniform mat4 ProjectionViewWorld; \
							void main() { vColour = Colour; \
							gl_Position = ProjectionViewWorld * Position; }";

	const char* fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 FragColor; \
							void main() { FragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	// check that it compiled and linked correctly
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}


	// we don't need to keep the individual shaders around
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

void Geometry::Plane()
{
	Vertex vertices[4];
	unsigned int indices[4] = { 0,2,1,3 };

	vertices[0].position = vec4(-5, 0, -5, 1);
	vertices[1].position = vec4(5, 0, -5, 1);
	vertices[2].position = vec4(-5, 0, 5, 1);
	vertices[3].position = vec4(5, 0, 5, 1);

	vertices[0].colour = vec4(1, 0, 0, 1);
	vertices[1].colour = vec4(0, 1, 0, 1);
	vertices[2].colour = vec4(0, 0, 1, 1);
	vertices[3].colour = vec4(1, 1, 1, 1);

	glGenBuffers(1, &m_VBO_Plane);
	glGenBuffers(1, &m_IBO_Plane);

	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &m_VAO_Plane);
	glBindVertexArray(m_VBO_Plane);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Plane);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO_Plane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned int), indices, GL_STATIC_DRAW);



	//i need to give the information for the layout location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
}

void Geometry::Square(const int &width, const int &height)
{
	Vertex vertices[8];
	unsigned int indices[18] = { 0,1,2,3,5,6,3,7,5,4,2,7,3,1,6,5,3 };

	const int top = height;
	const int bottom = -height;

	vertices[0].position = vec4(-width, bottom, -height, 1);
	vertices[1].position = vec4(width, bottom, -height, 1);
	vertices[2].position = vec4(-width, bottom, height, 1);
	vertices[3].position = vec4(width, bottom, height, 1);
	vertices[4].position = vec4(-width, top, height, 1);
	vertices[5].position = vec4(width, top, height, 1);
	vertices[6].position = vec4(width, top, -height, 1);
	vertices[7].position = vec4(-width, top, -height, 1);

	vertices[0].colour = vec4(1, 0, 0, 1);
	vertices[1].colour = vec4(1, 1, 0, 1);
	vertices[2].colour = vec4(1, 0, 1, 1);
	vertices[3].colour = vec4(0, 1, 1, 1);
	vertices[4].colour = vec4(0, 1, 0, 1);
	vertices[5].colour = vec4(0, 0, 1, 1);
	vertices[6].colour = vec4(1, 1, 1, 1);
	vertices[7].colour = vec4(0, 0, 0, 1);

	glGenBuffers(1, &m_VBO_Square);
	glGenBuffers(1, &m_IBO_Square);

	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &m_VAO_Square);
	glBindVertexArray(m_VAO_Square);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Square);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO_Square);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//i need to give the information for the layout location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
}

bool Geometry::Sphere(const int radius, bool isfilled)
{
	Vertex vertices[24];
	unsigned int indinces[24] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };

	for (int i = 0; i <= 23; i++)
	{
		double angle = 3.14159 * i / 22;

		double X = cos(angle) * radius;

		double Z = sin(angle) * radius;

		vertices[i].position = vec4(X, 0, Z, 1);
		vertices[i].colour = vec4(1, 0, 1, 1);
	}

	vertices[4].colour = vec4(0, 1, 0, 1);
	vertices[5].colour = vec4(0, 0, 1, 1);
	vertices[6].colour = vec4(1, 1, 1, 1);
	vertices[7].colour = vec4(0, 0, 0, 1);
	vertices[8].colour = vec4(0, 1, 0, 1);;
	vertices[15].colour = vec4(0, 0, 1, 1);
	vertices[16].colour = vec4(1, 1, 1, 1);
	vertices[17].colour = vec4(0, 0, 0, 1);
	vertices[21].colour = vec4(1, 0, 0, 1);
	vertices[22].colour = vec4(1, 1, 1, 1);
	vertices[23].colour = vec4(1, 0, 0, 1);

	//step 1 generate buffers
	glGenBuffers(1, &m_VBO_Sphere);
	glGenBuffers(1, &m_IBO_Sphere);
	//generate vertex arrays
	glGenVertexArrays(1, &m_VAO_Sphere);
	//bind vertex arrays
	glBindVertexArray(m_VAO_Sphere);
	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Sphere);
	//set buffer data for vertices
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	//set buffer data for indinces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO_Sphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(unsigned int), indinces, GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	return true;
}
bool Geometry::startup()
{
	createWindow("AIE OpenGL Application", 1280, 900);

	m_cam = new Camera(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	m_cam->setLookAtFrom(vec3(10, 10, 10), vec3(0));
		
	Plane();
	Square(5,5);
	Sphere(6, true);
	generateShader();

	return true;
}

void Geometry::shutdown()
{
	delete m_cam;

	destroyWindow();
}

bool Geometry::update(float deltatime)
{
	if (glfwWindowShouldClose(m_window) == false || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return true;
	}
}

void Geometry::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind shader
	glUseProgram(m_programID);

	// where to send the matrix
	int matUniform = glGetUniformLocation(m_programID, "ProjectionViewWorld");

	//drawing plane
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView()* glm::translate(vec3(5, 5, -5))));
	glBindVertexArray(m_VAO_Plane);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)0);

	//drawing square
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView() * glm::translate(vec3(-25, -10, 0))));
	glBindVertexArray(m_VAO_Square);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, (void*)0);

	//drawing Sphere
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, glm::value_ptr(m_cam->getProjectionView() * glm::translate(vec3(-4, -3, -4))));
	glBindVertexArray(m_VAO_Sphere);
	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_INT, (void*)0);
}

void Geometry::inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Geometry* myThis = (Geometry*)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_SPACE)
		if (action == GLFW_PRESS)
			myThis->m_dir = true;
		else if (action == GLFW_RELEASE)
			myThis->m_dir = false;
}