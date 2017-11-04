#ifndef SH_INPUT_MANAGER_H
#define SH_INPUT_MANAGER_H

#include <Commons.h>
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "ShString.h"
#include "ShMultiMap.h"
#include "ShList.h"
#include "ShObject.h"

namespace Shady
{

	
	using AxisFunc = void (Object::*)(f32 value);
	using ButtonFunc = void (Object::*)();
	
	using ButtonFuncS = void (*)();
	using AxisFuncS = void (*)(f32 value);

	#define IM_BFUNC(Func) (reinterpret_cast<ButtonFunc>(&Func))
	#define IM_AFUNC(Func) (reinterpret_cast<AxisFunc>(&Func))


	enum ButtonAction
	{
		BA_INVALID,
		BA_PRESSED,
		BA_RELEASED,
		BA_CLICKED
	};

	struct InputAction
	{
		String name;
		ButtonAction trigger;
		Object* obj;
		ButtonFunc func;
		ButtonFuncS funcS;
		f32 timeToProc;
		f32 timePassed;
		b8 keyState;
		b8 isTimed;

		InputAction() = default;
		
		InputAction(String n, ButtonAction t, Object* o, ButtonFunc f, f32 ttp = 0.0f):
					name{n}, trigger{t}, obj{o}, func{f}, funcS{nullptr},
					timeToProc{ttp}, timePassed{0.0f}, keyState{false}, isTimed{false} 
					{}
		InputAction(String n, ButtonAction t, ButtonFuncS f, f32 ttp = 0.0f):
					name{n}, trigger{t}, obj{nullptr}, func{nullptr}, funcS{f},
					timeToProc{ttp}, timePassed{0.0f}, keyState{false}, isTimed{false}
					{}

	};

	struct InputAxis
	{
		String name;
		Object* obj;
		AxisFunc func;
		AxisFuncS funcS;
		f32 timeToProc;
		f32 timePassed;
		f32 state; //Used only for mouse input

		InputAxis() = default;

		InputAxis(String n, Object* o, AxisFunc f, f32 ttp = 0.0f):
				 name{n}, obj{o}, func{f}, funcS{nullptr}, timeToProc{ttp},
				 timePassed{0.0f}, state{0.0f}
				 {}
		InputAxis(String n, AxisFuncS f, f32 ttp = 0.0f):
				 name{n}, obj{nullptr}, func{nullptr}, funcS{f}, timeToProc{ttp},
				 timePassed{0.0f}, state{0.0f}
				 {}

	};

	struct AxisValue
	{
		InputKey key;
		f32 scale;
	};

	

	class InputManager
	{
	private:
		static InputManager* sInstance;
		InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(const InputManager&& other) = delete;
		InputManager operator=(const InputManager& other) = delete;

		void RunAction(InputAction& in);
		void RunAxis(InputAxis& in, f32 val);

		Keyboard* mKeyboard;
		Mouse* mMouse;
		MultiMap<String, InputKey> mBMappings;
		MultiMap<String, List<AxisValue>> mAMappings;
		List<InputAction> mBoundActions;
		List<InputAxis> mBoundAxis;

	public:
		
		static InputManager* GetInstance();
		void Update(f32 dt);
		void MapAction(const String& name, InputKey key);
		void BindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func, f32 time = 0.0f);
		void BindAction(const String& name, ButtonAction action, ButtonFuncS func, f32 time = 0.0f);
		void MapAxis(const String& name, InputKey key, f32 scale);
		void BindAxis(const String& name, Object* obj, AxisFunc func, f32 time = 0.0f);
		void BindAxis(const String& name, AxisFuncS func, f32 time  = 0.0f);

	};
}

#endif