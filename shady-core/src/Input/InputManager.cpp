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

	//Call this with reinterpret_cast to ButtonFunc or with IM_BFUNC(Func) macro
	void InputManager::bindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func, f32 time)
	{
		if(mBMappings.hasKey(name))
		{
			InputAction temp(name, action, obj, func, time);
			mBoundActions.pushBack(temp);
		}	
	}
	void InputManager::bindAction(const String& name, ButtonAction action, ButtonFuncS func, f32 time)
	{
		if(mBMappings.hasKey(name))
		{
			InputAction temp(name, action, func, time);
			mBoundActions.pushBack(temp);
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

	//Call this with reinterpret_cast to AxisFunc or with IM_AFUNC(Func) macro
	void InputManager::bindAxis(const String& name, Object* obj, AxisFunc func, f32 time)
	{
		if(mAMappings.hasKey(name))
		{
			InputAxis temp(name, obj, func, time);
			mBoundAxis.pushBack(temp);
		}
	}

	void InputManager::bindAxis(const String& name, AxisFuncS func, f32 time)
	{
		if(mAMappings.hasKey(name))
		{
			InputAxis temp(name, func, time);
			mBoundAxis.pushBack(temp);
		}
	}

	void InputManager::update(f32 dt)
	{
	
		for(InputAction& in : mBoundActions)
		{
			b8 canProc = false;
			b8 completed = false;
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
			if(in.timeToProc > 0.0f)
			{
				if(in.isTimed)
				{
					in.timePassed += dt;
					if(currentState != in.keyState)
					{
						in.isTimed = false;
						in.timePassed = 0.0f;
						canProc = true;
					}
					else if((in.timePassed / 1000.0f) >= in.timeToProc)
					{
						in.timePassed = 0.0f;
						in.isTimed = false;
						canProc = true;
						completed = true;
					}
				}
				else
				{
					canProc = true;
				}	
			}
			else
			{
				canProc = (currentState != in.keyState);
				completed = true;
			}
			
			if(canProc)
			{
				switch(in.trigger)
				{
					case ButtonAction::BA_PRESSED:
					{
						if(currentState)
						{
							if(completed)
							{
								runAction(in);
							}
							else
							{
								in.isTimed = true;
							}
						}
					}break;
					case ButtonAction::BA_RELEASED:
					{
						if(!currentState)
						{
							runAction(in);
						}
					}break;
					case ButtonAction::BA_CLICKED:
					{
						if(!currentState)
						{
							runAction(in);
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
			

			for(AxisValue& val : vals)
			{
				if(val.key <= InputKey::MOUSE_Y)
				{
					f32 currentPos = mMouse->getValue(val.key); 
					finalValue = (currentPos - in.state) * val.scale;
					in.state = currentPos;
					runAxis(in, finalValue);
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
				runAxis(in, finalValue);
			}
		}

	}

	void InputManager::runAction(InputAction& in)
	{
		ButtonFunc pFunc = in.func;
		if(pFunc && in.obj)
		{
			(in.obj->*pFunc)();	
		}
		else if(in.funcS)
		{
			in.funcS();
		}
	}
	void InputManager::runAxis(InputAxis& in, f32 val)
	{
		AxisFunc pFunc = in.func;
		if(pFunc && in.obj) 
		{
			(in.obj->*pFunc)(val);
		}
		else if(in.funcS)
		{
			in.funcS(val);
		}
	}

}//namespace Shady