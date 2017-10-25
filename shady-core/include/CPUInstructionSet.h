#ifndef CPU_INSTRUCTION_SET_H
#define CPU_INSTRUCTION_SET_H

#include "Commons.h"
#include "ShString.h"
#include <intrin.h> 
#include <string>

namespace Shady
{
	struct CPUInstructionSet
	{
		
		b8 mIsIntel;
		b8 mIsAmd;
		b8 mMMX;
		b8 mSSE;
		b8 mSSE2;
		b8 mSSE3;
		b8 mSSSE3;
		b8 mSSE41;
		b8 mSSE42;
		b8 mAVX;
		b8 mAVX2;
		b8 mAVX512F;
		b8 mAVX512PF;
		b8 mAVX512ER;
		b8 mAVX512CD;
		b8 mFMA;
		b8 mSHA;
		
		

		String mBrand;

		CPUInstructionSet(): mIsIntel{false}, mIsAmd{false}
		{
			s32 ids;
			s32 xids;
			s32 data[4];
			s32& EAX = data[0];
			s32& EBX = data[1];
			s32& ECX = data[2];
			s32& EDX = data[3];
			__cpuid(data, 0);
			ids = EAX;

			__cpuid(data, 0); 
			c8 vendor[32];
			memset(vendor, 0, sizeof(vendor));
			*reinterpret_cast<s32*>(vendor) = EBX; 
			*reinterpret_cast<s32*>(vendor + 4) = EDX; 
			*reinterpret_cast<s32*>(vendor + 8) = ECX; 
			
			String vd = vendor;
			if(vd == "GenuineIntel")
			{
				mIsIntel = true;
			}
			else if(vd == "AuthenticAMD")
			{
				mIsAmd = true;
			}


			if (ids >= 1)
			{
				__cpuid(data, 1);
				mMMX = EDX & (1 << 23);
				mSSE = EDX & (1 << 25);
				mSSE2 = EDX & (1 << 26);
				mSSE3 = ECX & (1 << 0);
				mSSSE3 = ECX & (1 << 9);
				mSSE41 = ECX & (1 << 19);
				mSSE42 = ECX & (1 << 20);
				mAVX = ECX & (1 << 28);
				mFMA = ECX & (1 << 12);
			}

			if (ids >= 7)
			{
				__cpuid(data, 7);
				mAVX2 = EBX & (1 << 5);
				mAVX512F = EBX & (1 << 16);
				mAVX512PF = EBX & (1 << 26);
				mAVX512ER = EBX & (1 << 27);
				mAVX512CD = EBX & (1 << 28);
				mSHA = EBX & (1 << 29);
			}
		}

	};

	class CPU
	{
	public:

		static CPUInstructionSet sCPU;
		
		static b8 IsIntel() {return sCPU.mIsIntel;}
		static b8 IsAmd() {return sCPU.mIsAmd;}
		static b8 MMX() {return sCPU.mMMX;}
		static b8 SSE() {return sCPU.mSSE;}
		static b8 SSE2() {return sCPU.mSSE2;}
		static b8 SSE3() {return sCPU.mSSE3;}
		static b8 SSSE3() {return sCPU.mSSSE3;}
		static b8 SSE41() {return sCPU.mSSE41;}
		static b8 SSE42() {return sCPU.mSSE42;}
		static b8 AVX() {return sCPU.mAVX;}
		static b8 AVX2() {return sCPU.mAVX2;}
		static b8 AVX512F() {return sCPU.mAVX512F;}
		static b8 AVX512PF() {return sCPU.mAVX512PF;}
		static b8 AVX512ER() {return sCPU.mAVX512ER;}
		static b8 AVX512CD() {return sCPU.mAVX512CD;}
		static b8 FMA() {return sCPU.mFMA;}
		static b8 SHA() {return sCPU.mSHA;}
	};
}

#endif