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
		BA_RELEASED
	};

	struct InputAction
	{
		String name;
		ButtonAction trigger;
		Object* obj;
		ButtonFunc func;
		ButtonFunc2 func2;
		b8 keyState;
	};

	struct AxisValue
	{
		InputKey key;
		f32 scale;
	};

	struct InputAxis
	{
		String name;
		Object* obj;
		AxisFunc func;
		AxisFunc2 func2;
		f32 state; //Used only for mouse input
	};

	class InputManager
	{
	private:
		static InputManager* sInstance;
		InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(const InputManager&& other) = delete;
		InputManager operator=(const InputManager& other) = delete;
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
		void bindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func);
		void bindAction(const String& name, ButtonAction action, ButtonFunc2 func);
		void mapAxis(const String& name, InputKey key, f32 scale);
		void bindAxis(const String& name, Object* obj, AxisFunc func);
		void bindAxis(const String& name, AxisFunc2 func);

	};
}

#endif