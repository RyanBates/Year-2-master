#pragma once
#include "BaseApplication.h"
#include <Camera.h>

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
	 void generateGrid();
	 void generateShader();

	 bool update(float deltatime) override;
	 void draw_Rect();
	 void draw_Sphere();
	 void draw() override;
	 void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_programID;	

	Camera* m_cam;
	bool m_dir;
};