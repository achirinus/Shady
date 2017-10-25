#include "Renderer3D.h"

namespace Shady
{

	Renderer3D::Renderer3D(Camera3D* cam):
		mCam{cam}, mLastCam{nullptr}, mRenderQueue{}
	{

	}

	b8 Renderer3D::changeCamera(Camera3D* cam)
	{
		b8 result = false;
		if(cam)
		{
			mLastCam = mCam;
			mCam = cam;
			result = true;
		}
		else
		{
			if(mLastCam)
			{
				Camera3D* temp = mLastCam;
				mLastCam = mCam;
				mCam = temp;
				result = true;
			}
		}

		return result;
	}

	void Renderer3D::submit(Renderable3D* rend)
	{
		mRenderQueue.push(rend);
	}

	void Renderer3D::render(f32 dt)
	{
		while(mRenderQueue.size())
		{
			Renderable3D* model = mRenderQueue.pop();
			model->mShader->enable();
			model->mShader->setUniformMat4("viewMat", mCam->GetViewMat());
			model->mShader->setUniformMat4("projMat", mCam->GetProjMat());
			model->draw();
			model->mShader->disable();
		}
	}

} // namespace Shady
