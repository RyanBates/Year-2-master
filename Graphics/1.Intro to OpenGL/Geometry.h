#pragma once
#include "BaseApplication.h"
#include "Camera.h"

struct Vertex {
	glm::vec4 position;
	glm::vec4 colour;
};

class Geometry : public BaseApplication
{
public:
	Geometry();
	~Geometry();

	 bool startup() override;
	 void shutdown() override;
	 void Plane();
	 void Square(const int &width, const int &height);
	 bool Sphere(const int radius, bool isfilled);
	 void generateShader();

	 bool update(float deltatime) override;

	 void draw() override;
	 void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	unsigned int m_VAO_Plane, m_VAO_Square, m_VAO_Sphere;
	unsigned int m_VBO_Plane, m_VBO_Square, m_VBO_Sphere;
	unsigned int m_IBO_Plane, m_IBO_Square, m_IBO_Sphere;

	unsigned int m_programID;	

	Camera* m_cam;
	bool m_dir;
};