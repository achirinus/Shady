#ifndef DEBUGHELPER_H 
#define DEBUGHELPER_H

#include "StringUtils.h"
#include <Window.h>
#include "ShArray.h"

namespace Shady
{
#define AUTO_TIMED_FUNCTION() DebugFunctionAutoTimer __FUNCTION__##autoTimer{__FUNCTION__};

#define START_TIMED_BLOCK(name) DebugFunctionManualTimer name##manualTimer{#name};
#define END_TIMED_BLOCK(name) name##manualTimer.CalculateData();

	struct DebugFunctionData
	{
		c8 Name[56];
		f32 ExecuteTimeMili;
		s32 NumOfCalls;
		f32 AvgTimePerCall;
	};

	struct FrameInfo
	{
		Array<DebugFunctionData> Functions;
	};

	struct DebugHelper
	{
		static FrameInfo LastFrame;
		static FrameInfo CurrentFrame;
		static void AddFunctionData(DebugFunctionData FunctionData);
		static void StartFrame();
		static void EndFrame();
	};

	struct DebugFunctionAutoTimer
	{
		DebugFunctionData FData;
		LARGE_INTEGER Freq;
		LARGE_INTEGER StartTime;
		DebugFunctionAutoTimer(const c8* FunctionName)
		{
			StrCopy(FData.Name, FunctionName);
			QueryPerformanceCounter(&StartTime);
			QueryPerformanceFrequency(&Freq);
		}

		void CalculateData()
		{
			LARGE_INTEGER EndTime;
			QueryPerformanceCounter(&EndTime);

			s64 Clocks = EndTime.QuadPart - StartTime.QuadPart;
			FData.ExecuteTimeMili = (f32)(((f64)Clocks * 1000.0) / (f64)Freq.QuadPart);
			FData.AvgTimePerCall = FData.ExecuteTimeMili;
			FData.NumOfCalls = 1;
			DebugHelper::AddFunctionData(FData);
		}

		~DebugFunctionAutoTimer()
		{
			CalculateData();
		}
	};

	struct DebugFunctionManualTimer
	{
		DebugFunctionData FData;
		LARGE_INTEGER Freq;
		LARGE_INTEGER StartTime;
		DebugFunctionManualTimer(const c8* FunctionName)
		{
			StrCopy(FData.Name, FunctionName);
			QueryPerformanceCounter(&StartTime);
			QueryPerformanceFrequency(&Freq);
		}

		void CalculateData()
		{
			LARGE_INTEGER EndTime;
			QueryPerformanceCounter(&EndTime);

			s64 Clocks = EndTime.QuadPart - StartTime.QuadPart;
			FData.ExecuteTimeMili = (f32)(((f64)Clocks * 1000.0) / (f64)Freq.QuadPart);
			FData.AvgTimePerCall = FData.ExecuteTimeMili;
			FData.NumOfCalls = 1;
			DebugHelper::AddFunctionData(FData);
		}
	};

	
}
#endif
