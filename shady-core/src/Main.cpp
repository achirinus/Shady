#include <Commons.h>

#include <glew.h>
#include "ShadyApp.h"
#include "ShString.h"
#include "FileUtils.h"
#include "ModelLoader.h"
#include "ShadyMath.h"

using namespace Shady;

int main(int argc, const char* argv[])
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	
	ShadyApp* app = ShadyApp::getInstance();
	app->start();
	
	return 0;

}




