#pragma once

#include "BaseApplication.h"
#include <Camera.h>
class Geometry : public BaseApplication
{
public:
	Geometry();
	~Geometry();

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltatime);
	virtual void draw();

};

