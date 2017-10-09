#include "InputManager.h"

namespace Shady
{
	InputManager* InputManager::sInstance = nullptr;

	InputManager::InputManager(): mBoundActions{}, mBMappings{}
	{
		mKeyboard = Keyboard::getInstance();
		mMouse = Mouse::getInstance();
	}

	InputManager* InputManager::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new InputManager();
		}
		return sInstance;
	}

	void InputManager::mapAction(const String& name, InputKey key)
	{
		mBMappings.add(name, key);
	}

	void InputManager::bindAction(const String& name, ButtonAction action, ButtonFunc func)
	{
		if(mBMappings.hasKey(name))
		{
			mBoundActions.pushBack({name, action, func, false});
		}	
	}

	void InputManager::update(f32 dt)
	{
		
		for(InputAction& in : mBoundActions)
		{
			InputKey key = mBMappings[in.name];
			b8 currentState = false;
			if(key <= InputKey::MOUSE_MIDDLE)
			{
				currentState = mMouse->getState(key);
			}
			else
			{
				currentState = mKeyboard->isPressed(key);
			}
			if(currentState != in.keyState)
			{
				switch(in.trigger)
				{
					case ButtonAction::BA_PRESSED:
					{
						if(currentState)
						{
							ButtonFunc pFunc = in.func;
							if(pFunc) pFunc();
						}
					}break;
					case ButtonAction::BA_RELEASED:
					{
						if(!currentState)
						{
							ButtonFunc pFunc = in.func;
							if(pFunc) pFunc();
						}
					}break;
				}
				in.keyState = currentState;	
			}
			
		}
	
	}
}