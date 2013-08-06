#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

namespace System
{

	const long PUNK_KEY_LEFT_ALT = 0x01;
    const long PUNK_KEY_RIGHT_ALT =0x02;
	const long PUNK_KEY_CAPSLOCK =0x04;
	const long PUNK_KEY_PAGE_UP =0x05;
	const long PUNK_KEY_PAGE_DOWN =0x06;
	const long PUNK_KEY_BACKSPACE = 0x08;
	const long PUNK_KEY_TAB = 0x09;
    const long PUNK_KEY_ENTER = 0x0D;
	const long PUNK_KEY_SHIFT = 0x10;
	const long PUNK_KEY_CONTROL = 0x11;
	const long PUNK_KEY_ALT = 0x12;

	const long PUNK_KEY_ESCAPE = 0x1B;
	const long PUNK_KEY_SPACE = 0x20;
	const long PUNK_KEY_END = 0x23;
	const long PUNK_KEY_HOME = 0x24;

	const long PUNK_KEY_LEFT = 0x25;
	const long PUNK_KEY_UP = 0x26;
    const long PUNK_KEY_RIGHT = 0x27;
	const long PUNK_KEY_DOWN = 0x28;

    const long PUNK_KEY_INSERT =0x2D;
	const long PUNK_KEY_DELETE =0x2E;

	const long PUNK_KEY_0 = 0x30;
	const long PUNK_KEY_1 = 0x31;
	const long PUNK_KEY_2 = 0x32;
	const long PUNK_KEY_3 = 0x33;
	const long PUNK_KEY_4 = 0x34;
	const long PUNK_KEY_5 = 0x35;
	const long PUNK_KEY_6 = 0x36;
	const long PUNK_KEY_7 = 0x37;
	const long PUNK_KEY_8 = 0x38;
	const long PUNK_KEY_9 = 0x39;

	const long PUNK_KEY_A = 0x41;
	const long PUNK_KEY_B = 0x42;
	const long PUNK_KEY_C = 0x43;
	const long PUNK_KEY_D = 0x44;
	const long PUNK_KEY_E = 0x45;
	const long PUNK_KEY_F = 0x46;
	const long PUNK_KEY_G = 0x47;
	const long PUNK_KEY_H = 0x48;
    const long PUNK_KEY_I = 0x49;
    const long PUNK_KEY_J = 0x4A;
	const long PUNK_KEY_K = 0x4B;
	const long PUNK_KEY_L = 0x4C;
    const long PUNK_KEY_M = 0x4D;
	const long PUNK_KEY_N = 0x4E;
	const long PUNK_KEY_O = 0x4F;
	const long PUNK_KEY_P = 0x50;
	const long PUNK_KEY_Q = 0x51;
    const long PUNK_KEY_R = 0x52;
	const long PUNK_KEY_S = 0x53;
	const long PUNK_KEY_T = 0x54;
	const long PUNK_KEY_U = 0x55;
	const long PUNK_KEY_V = 0x56;
	const long PUNK_KEY_W = 0x57;
	const long PUNK_KEY_X = 0x58;
	const long PUNK_KEY_Y = 0x59;
	const long PUNK_KEY_Z = 0x5A;

	const long PUNK_KEY_NUM0 = 0x60;
	const long PUNK_KEY_NUM1 = 0x61;
	const long PUNK_KEY_NUM2 = 0x62;
	const long PUNK_KEY_NUM3 = 0x63;
	const long PUNK_KEY_NUM4 = 0x64;
	const long PUNK_KEY_NUM5 = 0x65;
	const long PUNK_KEY_NUM6 = 0x66;
	const long PUNK_KEY_NUM7 = 0x67;
	const long PUNK_KEY_NUM8 = 0x68;
	const long PUNK_KEY_NUM9 = 0x69;

	const long PUNK_KEY_F1 = 0x70;
	const long PUNK_KEY_F2 = 0x71;
	const long PUNK_KEY_F3 = 0x72;
	const long PUNK_KEY_F4 = 0x73;
	const long PUNK_KEY_F5 = 0x74;
	const long PUNK_KEY_F6 = 0x75;
	const long PUNK_KEY_F7 = 0x76;
	const long PUNK_KEY_F8 = 0x77;
	const long PUNK_KEY_F9 = 0x78;
	const long PUNK_KEY_F10 = 0x79;
	const long PUNK_KEY_F11 = 0x7A;
	const long PUNK_KEY_F12 = 0x7B;
	
	const long PUNK_KEY_LEFT_SHIFT = 0xA0;
    const long PUNK_KEY_RIGHT_SHIFT = 0xA1;
	const long PUNK_KEY_LEFT_CONTROL = 0xA2;
    const long PUNK_KEY_RIGHT_CONTROL = 0xA3;

	const long MAX_EVENTS_COUNT = 0x0800;

	const long EVENT_IDLE	 = 0x0000;
	const long EVENT_MOUSE_MOVE	 = 0x0001;
	const long EVENT_MOUSE_WHEEL = 0x0002;
	const long EVENT_KEY_DOWN = 0x0003;
	const long EVENT_KEY_UP = 0x0004;
    const long EVENT_KEY_CHAR = 0x0005;
	const long EVENT_MOUSE_LBUTTON_DOWN = 0x0006;
	const long EVENT_MOUSE_LBUTTON_UP = 0x0007;
	const long EVENT_MOUSE_RBUTTON_DOWN = 0x0008;
	const long EVENT_MOUSE_RBUTTON_UP = 0x0009;
	const long EVENT_MOUSE_MBUTTON_DOWN = 0x000A;
	const long EVENT_MOUSE_MBUTTON_UP = 0x000B;
	const long EVENT_WINDOW_RESIZE		= 0x000C;
	const long EVENT_MOUSE_ENTER		= 0x000D;
	const long EVENT_MOUSE_LEAVE		= 0x000E;
	const long EVENT_SET_FOCUSED		= 0x000F;
	const long EVENT_SET_UNFOCUSED		= 0x0010;
	const long EVENT_KEY_WCHAR			= 0x0011;
	const long EVENT_MOUSE_HOOVER		= 0x0012;
	const long EVENT_LAST_EVENT			= 0x0013;

	const long EVENT_INSTANCE_CHANGED_LOCATION = 0x0014;
	const long EVENT_INSTANCE_DESTROYED = 0x0015;
	const long EVENT_INSTANCE_CHANGED_parent = 0x0016;
	const long EVENT_INSTANCE_APPEARED = 0x0017;

	const long EVENT_MODEL_TIME_STEP	= 0x0018;
	const long EVENT_MODULE_LOGIC_EVENTS = 0x0100;
}

#endif // EVENT_TYPE_H
