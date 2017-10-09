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
		List<InputAction> mBoundActions;
	public:
		
		static InputManager* getInstance();
		void update(f32 dt);
		void mapAction(const String& name, InputKey key);
		void bindAction(const String& name, ButtonAction action, ButtonFunc func);
	};
}

#endif