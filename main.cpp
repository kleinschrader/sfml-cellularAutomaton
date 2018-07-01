#include "cApplication.h"

int main()
{
	cApplication *App = new cApplication;
	App->run();
	delete App;
    return 0;
}
