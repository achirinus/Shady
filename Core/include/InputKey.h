#ifndef SH_INPUT_KEY_H
#define SH_INPUT_KEY_H

namespace Shady
{
	//Some of these(like KEY_TILDA) are only accurate for US layout
	enum InputKey
	{


		MOUSE_X = 0x03,
		MOUSE_Y = 0x04,
		MOUSE_LEFT = 0x05,
		MOUSE_RIGHT = 0x06,
		MOUSE_MIDDLE = 0x07,
		KEY_BACK = 0x08,
		KEY_TAB = 0x09,
		KEY_CLEAR = 0x0C,
		KEY_RETURN = 0x0D,
		KEY_SHIFT = 0x10,
		KEY_CONTROL = 0x11,
		KEY_ALT = 0x12,
		KEY_PAUSE = 0x13,
		KEY_CAPS = 0x14,
		KEY_ESC = 0x1B,
		KEY_SPACE = 0x20,
		KEY_PGUP = 0x21,
		KEY_PGDOWN = 0x22,
		KEY_END = 0x23,
		KEY_HOME = 0x24,
		KEY_LEFT = 0x25,
		KEY_UP = 0x26,
		KEY_RIGHT = 0x27,
		KEY_DOWN = 0x28,
		KEY_SELECT = 0x29,
		KEY_PRINT = 0x2A,
		KEY_INSERT = 0x2D,
		KEY_DEL = 0x2E,
		KEY_0 = 0x30,
		KEY_1 = 0x31,
		KEY_2 = 0x32,
		KEY_3 = 0x33,
		KEY_4 = 0x34,
		KEY_5 = 0x35,
		KEY_6 = 0x36,
		KEY_7 = 0x37,
		KEY_8 = 0x38,
		KEY_9 = 0x39,
		KEY_A = 0x41,
		KEY_B = 0x42,
		KEY_C = 0x43,
		KEY_D = 0x44,
		KEY_E = 0x45,
		KEY_F = 0x46,
		KEY_G = 0x47,
		KEY_H = 0x48,
		KEY_I = 0x49,
		KEY_J = 0x4A,
		KEY_K = 0x4B,
		KEY_L = 0x4C,
		KEY_M = 0x4D,
		KEY_N = 0x4E,
		KEY_O = 0x4F,
		KEY_P = 0x50,
		KEY_Q = 0x51,
		KEY_R = 0x52,
		KEY_S = 0x53,
		KEY_T = 0x54,
		KEY_U = 0x55,
		KEY_V = 0x56,
		KEY_W = 0x57,
		KEY_X = 0x58,
		KEY_Y = 0x59,
		KEY_Z = 0x5A,
		KEY_LWIN = 0x5B,
		KEY_RWIN = 0x5C,
		KEY_NUM0 = 0x60,
		KEY_NUM1 = 0x61,
		KEY_NUM2 = 0x62,
		KEY_NUM3 = 0x63,
		KEY_NUM4 = 0x64,
		KEY_NUM5 = 0x65,
		KEY_NUM6 = 0x66,
		KEY_NUM7 = 0x67,
		KEY_NUM8 = 0x68,
		KEY_NUM9 = 0x69,
		KEY_F1 = 0x70,
		KEY_F2 = 0x71,
		KEY_F3 = 0x72,
		KEY_F4 = 0x73,
		KEY_F5 = 0x74,
		KEY_F6 = 0x75,
		KEY_F7 = 0x76,
		KEY_F8 = 0x77,
		KEY_F9 = 0x78,
		KEY_F10 = 0x79,
		KEY_F11 = 0x7A,
		KEY_F12 = 0x7B,
		KEY_LSHIFT = 0xA0,
		KEY_RSHIFT = 0xA1,
		KEY_LCONTROL = 0xA2,
		KEY_RCONTROL = 0xA3,
		KEY_TILDA = 0xC0,

		MAX_KEYS_SUPPORTED = 0xFF
	};

	
}

#endif