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

	void InputManager::bindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func)
	{
		if(mBMappings.hasKey(name))
		{
			mBoundActions.pushBack({name, action, obj, func, nullptr, false});
		}	
	}
	void InputManager::bindAction(const String& name, ButtonAction action, ButtonFunc2 func)
	{
		if(mBMappings.hasKey(name))
		{
			mBoundActions.pushBack({name, action, nullptr, nullptr, func, false});
		}	
	}
	void InputManager::mapAxis(const String& name, InputKey key, f32 scale)
	{
		if(mAMappings.hasKey(name))
		{
			mAMappings[name].pushBack({key, scale});
		}
		else
		{
			List<AxisValue> vals = {};
			vals.pushBack({key, scale});
			mAMappings.add(name, vals);
		}
	}
	void InputManager::bindAxis(const String& name, Object* obj, AxisFunc func)
	{
		if(mAMappings.hasKey(name))
		{
			mBoundAxis.pushBack({name, obj, func, nullptr, 0.0f});
		}
	}

	void InputManager::bindAxis(const String& name, AxisFunc2 func)
	{
		if(mAMappings.hasKey(name))
		{
			mBoundAxis.pushBack({name, nullptr, nullptr, func, 0.0f});
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
							if(pFunc && in.obj)
							{
								(in.obj->*pFunc)();	
							}
							else if(in.func2)
							{
								in.func2();
							}

						}
					}break;
					case ButtonAction::BA_RELEASED:
					{
						if(!currentState)
						{
							ButtonFunc pFunc = in.func;
							if(pFunc && in.obj)
							{
								(in.obj->*pFunc)();	
							}
							else if(in.func2)
							{
								in.func2();
							}
						}
					}break;
				}
				in.keyState = currentState;	
			}
		} // for mBoundActions
	
		for(InputAxis& in : mBoundAxis)
		{
			List<AxisValue>& vals = mAMappings[in.name];
			f32 finalValue = 0.0f;
			AxisFunc pFunc = in.func;

			for(AxisValue& val : vals)
			{
				if(val.key <= InputKey::MOUSE_Y)
				{
					f32 currentPos = mMouse->getValue(val.key); 
					finalValue = (currentPos - in.state) * val.scale;
					in.state = currentPos;
					if(pFunc && in.obj) 
					{
						(in.obj->*pFunc)(finalValue);
					}
					else if(in.func2)
					{
						in.func2(finalValue);
					}
				}
				else
				{
					if(mKeyboard->isPressed(val.key))
					{
						finalValue += val.scale;
					}
				}
			}
			if(finalValue)
			{
				if(pFunc && in.obj) 
				{
					(in.obj->*pFunc)(finalValue);
				}
				else if(in.func2)
				{
					in.func2(finalValue);
				}
			}
		}

	}
}