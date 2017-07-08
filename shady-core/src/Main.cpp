#include <Commons.h>

#include <glew.h>
#include "ShadyApp.h"

using namespace Shady;

using namespace Utils;


int main(int argc, const char* argv[])
{
	const GLubyte* glstr = glGetString(GL_EXTENSIONS);
	
	ShadyApp app = ShadyApp::getInstance();
	app.start();
	
	return 0;

}




