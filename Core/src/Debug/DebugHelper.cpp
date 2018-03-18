#include "DebugHelper.h"

namespace Shady
{
	FrameInfo DebugHelper::LastFrame;
	FrameInfo DebugHelper::CurrentFrame;

	void DebugHelper::AddFunctionData(DebugFunctionData FunctionData)
	{
		bool Exists = false;
		for (DebugFunctionData& TempData : CurrentFrame.Functions)
		{
			if (StrCompare(FunctionData.Name,TempData.Name))
			{
				Exists = true;
				TempData.ExecuteTimeMili += FunctionData.ExecuteTimeMili;
				TempData.NumOfCalls += FunctionData.NumOfCalls;
				TempData.AvgTimePerCall = TempData.ExecuteTimeMili / (f32)TempData.NumOfCalls;
				break;
			}
		}
		if(!Exists) CurrentFrame.Functions.Add(FunctionData);
	}

	void DebugHelper::StartFrame()
	{
		CurrentFrame = {};
	}

	void DebugHelper::EndFrame()
	{
		LastFrame = CurrentFrame;
	}
}