#ifndef SH_INPUT_MANAGER_H
#define SH_INPUT_MANAGER_H

#include <Commons.h>
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "ShString.h"
#include "ShMultiMap.h"
#include "ShList.h"


namespace Shady
{

	typedef void (*ButtonFunc)();
	typedef void (*AxisFunc)(f32 value);

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
		ButtonFunc func;
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
		AxisFunc func;
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
		void bindAction(const String& name, ButtonAction action, ButtonFunc func);
		void mapAxis(const String& name, InputKey key, f32 scale);
		void bindAxis(const String& name, AxisFunc func);
	};
}

#endif