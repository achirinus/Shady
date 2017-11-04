#include "InputManager.h"

namespace Shady
{
	InputManager* InputManager::sInstance = nullptr;

	InputManager::InputManager(): mBoundActions{}, mBMappings{}
	{
		mKeyboard = Keyboard::GetInstance();
		mMouse = Mouse::GetInstance();
	}

	InputManager* InputManager::GetInstance()
	{
		if(!sInstance)
		{
			sInstance = new InputManager();
		}
		return sInstance;
	}

	void InputManager::MapAction(const String& name, InputKey key)
	{
		mBMappings.Add(name, key);
	}

	//Call this with reinterpret_cast to ButtonFunc or with IM_BFUNC(Func) macro
	void InputManager::BindAction(const String& name, ButtonAction action, Object* obj, ButtonFunc func, f32 time)
	{
		if(mBMappings.HasKey(name))
		{
			mBoundActions.AddBack({name, action, obj, func, time});
		}	
	}
	void InputManager::BindAction(const String& name, ButtonAction action, ButtonFuncS func, f32 time)
	{
		if(mBMappings.HasKey(name))
		{
			mBoundActions.AddBack({name, action, func, time});
		}	
	}
	void InputManager::MapAxis(const String& name, InputKey key, f32 scale)
	{
		if(mAMappings.HasKey(name))
		{
			mAMappings[name].AddBack({key, scale});
		}
		else
		{
			List<AxisValue> vals = {};
			vals.AddBack({key, scale});
			mAMappings.Add(name, vals);
		}
	}

	//Call this with reinterpret_cast to AxisFunc or with IM_AFUNC(Func) macro
	void InputManager::BindAxis(const String& name, Object* obj, AxisFunc func, f32 time)
	{
		if(mAMappings.HasKey(name))
		{
			mBoundAxis.AddBack({name, obj, func, time});
		}
	}

	void InputManager::BindAxis(const String& name, AxisFuncS func, f32 time)
	{
		if(mAMappings.HasKey(name))
		{
			mBoundAxis.AddBack({name, func, time});
		}
	}

	void InputManager::Update(f32 dt)
	{
	
		for(InputAction& in : mBoundActions)
		{
			b8 canProc = false;
			b8 completed = false;
			InputKey key = mBMappings[in.name];
			b8 currentState = false;
			if(key <= InputKey::MOUSE_MIDDLE)
			{
				currentState = mMouse->GetState(key);
			}
			else
			{
				currentState = mKeyboard->IsPressed(key);
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
								RunAction(in);
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
							RunAction(in);
						}
					}break;
					case ButtonAction::BA_CLICKED:
					{
						if(!currentState)
						{
							RunAction(in);
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
					f32 currentPos = mMouse->GetValue(val.key); 
					finalValue = (currentPos - in.state) * val.scale;
					in.state = currentPos;
					RunAxis(in, finalValue);
				}
				else
				{
					if(mKeyboard->IsPressed(val.key))
					{
						finalValue += val.scale;
					}
				}
			}
			if(finalValue)
			{
				RunAxis(in, finalValue);
			}
		}

	}

	void InputManager::RunAction(InputAction& in)
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
	void InputManager::RunAxis(InputAxis& in, f32 val)
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