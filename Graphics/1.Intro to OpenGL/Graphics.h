#pragma once

#include "BaseApplication.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void startup();
	void shutdown();

	void update(float deltatime);
};