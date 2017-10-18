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

	typedef void (Object::*ButtonFunc)();
	typedef void (Object::*AxisFunc)(f32 value);

	//Used for static functions 
	typedef void (*ButtonFunc2)();
	typedef void (*AxisFunc2)(f32 value);

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
		ButtonFunc2 func2;
		f32 timeToProc;
		f32 timePassed;
		b8 keyState;
		b8 isTimed;
		InputAction(String n, ButtonAction t, Object* o, ButtonFunc f, f32 ttp = 0.0f):
					name{n}, trigger{t}, obj{o}, func{f}, func2{nullptr},
					timeToProc{ttp}, timePassed{0.0f}, keyState{false}, isTimed{false} 
					{}
		InputAction(String n, ButtonAction t, ButtonFunc2 f, f32 ttp = 0.0f):
					name{n}, trigger{t}, obj{nullptr}, func{nullptr}, func2{f},
					timeToProc{ttp}, timePassed{0.0f}, keyState{false}, isTimed{false}
					{}

	};

	struct InputAxis
	{
		String name;
		Object* obj;
		AxisFunc func;
		AxisFunc2 func2;
		f32 timeToProc;
		f32 timePassed;
		f32 state; //Used only for mouse input

		InputAxis(String n, Object* o, AxisFunc f, f32 ttp = 0.0f):
				 name{n}, obj{o}, func{f}, func2{nullptr}, timeToProc{ttp},
				 timePassed{0.0f}, state{0.0f}
				 {}
		InputAxis(String n, AxisFunc2 f, f32 ttp = 0.0f):
				 name{n}, obj{nullptr}, func{nullptr}, func2{f}, timeToProc{ttp},
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

		void runAction(InputAction& in);
		void runAxis(InputAxis& in, f32 val);

		Keyboard* mKeyboard;
		Mouse* mMouse;
		MultiMap<String, InputKey> mBMappings;
		MultiMap<String, List<AxisValue>> mAMappings;
		List<InputAction> mBoundActions;
		List<InputAxis> mBoundAxis;

	public:
		
		static InputManager* getInstance();
		void update(f32 dt);
		void mapAction(const String& name, InputKey key);
		void bindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func, f32 time = 0.0f);
		void bindAction(const String& name, ButtonAction action, ButtonFunc2 func, f32 time = 0.0f);
		void mapAxis(const String& name, InputKey key, f32 scale);
		void bindAxis(const String& name, Object* obj, AxisFunc func, f32 time = 0.0f);
		void bindAxis(const String& name, AxisFunc2 func, f32 time  = 0.0f);

	};
}

#endif