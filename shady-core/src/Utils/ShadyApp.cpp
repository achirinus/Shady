#include <ShadyApp.h>
#include "Win32Window.h"
#include "Shader.h"


#include "Sprite.h"
namespace Shady
{
	ShadyApp* ShadyApp::sInstance = 0;

	inline ShadyApp& ShadyApp::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new ShadyApp();
		}

		return *sInstance;
	}

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();
		#if 0
		ModelLoader mdl{};
		Mesh* cube = mdl.loadObj("..\\..\\data\\cube.obj");
		
		for(u32 vertIndex = 0; vertIndex < cube->mVertices.size(); vertIndex++)
		{
			DEBUG_OUT_INFO(cube->mVertices[vertIndex].toString().cStr());
		}
		#endif
		Shader shader{"..\\src\\Shaders\\basic_vert.shady", "..\\src\\Shaders\\basic_frag.shady"};
		f32 verts[] = 
		{
			-0.5f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f
		};

		Vec4f mat4[] =
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.5f, 0.0f, 0.0f, 1.0f}
		};

		Vec3f trans = {0.0f, 0.0f, 0.0f};
		
		Sprite sprite(Vec3f(-1.0f, -1.0f, 0.0f) , 1, 1);
		f32 step = 0.01f;
		while (mMainWindow->isOpen())
		{
			if(mKeyboard->isPressed(KEY_DOWN))
			{
				sprite.move(Vec3f(0.0f, -step, 0.0f));
			} 
			if(mKeyboard->isPressed(KEY_UP))
			{	
				sprite.move(Vec3f(0.0f, step, 0.0f));
			} 
			if(mKeyboard->isPressed(KEY_LEFT)) 
			{
				sprite.move(Vec3f(-step, 0.0f, 0.0f));
			}
			if(mKeyboard->isPressed(KEY_RIGHT)) 
			{
				sprite.move(Vec3f(step, 0.0f, 0.0f));	
				
			}
			if(mKeyboard->isCombo(2, KEY_RIGHT, KEY_S))
			{
				sprite.scale(0.01f);
			}
			if(mKeyboard->isCombo(2, KEY_LEFT, KEY_S))
			{
				sprite.scale(-0.01f);
			}
			mMainWindow->update();
			mMainWindow->clear();
			
			Matrix4f mat = sprite.getModelMat();

			shader.setUniformMat4("modelMat",  mat);
			shader.enable();	
			sprite.draw();
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			shader.disable();
			
			mMainWindow->swapBuffers();
		}
	}


}
