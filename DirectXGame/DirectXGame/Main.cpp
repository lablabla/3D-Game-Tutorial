
#include "AppWindow.h"


int main(int argc, char** argv)
{
	AppWindow app;

	if (app.init())
	{
		while (app.isRunning())
		{
			app.broadcast();
		}
	}
}