#include <BaseApplication.h>
#include <Graphics.h>

int main() 
{	
	BaseApplication * app = new Graphics();
	if (app->startup())
		app->run();
	app->shutdown();
	return 0;
}