using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;



namespace Engine
{
	public enum Key : uint
	{
		// Control keys
		BackSpace	= 0x08,
		Tab			= 0x09,
		Enter		= 0x0D,
		Shift		= 0x10,
		Ctrl		= 0x11,
		CapsLock	= 0x14,
		ESC			= 0x1B,
		Space		= 0x20,

		// Arrow keys
		LeftArrow	= 0x25,
		UpArrow,
		RightArrow,
		DownArrow,

		// 0 through 9 keys
		Alpha0 = 0x30,
		Alpha1,
		Alpha2,
		Alpha3,
		Alpha4,
		Alpha5,
		Alpha6,
		Alpha7,
		Alpha8,
		Alpha9,

		// A through Z keys
		A = 0x41,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		// 0 through 9 keys(number pad)
		NumberPad0 = 0x60,
		NumberPad1,
		NumberPad2,
		NumberPad3,
		NumberPad4,
		NumberPad5,
		NumberPad6,
		NumberPad7,
		NumberPad8,
		NumberPad9,

		Count,
	}


	public enum MouseButton : uint
	{
		Left	= 0x01,
		Right	= 0x02,
		Middle	= 0x10,

		Count,
	}


	[Flags]
	public enum ButtonState : byte
	{
		Default		= 0,

		Pressed		= 1 << 0,
		Released	= 1 << 1,

		Clicked		= Pressed | Released,
	};


	[StructLayout(LayoutKind.Explicit)]
	public struct Event
	{
		public enum Type : uint
		{
			WindowResized,
			WindowClosing,
			WindowFocused,

			Key,

			MouseButton,
			MouseMoved,
			MouseScrollWheelScrolled,
		}


		[FieldOffset(0)]
		public Type type;


		#region Union
		// if type == Type.WindowResized
		[FieldOffset(4)]
		public int width;
		[FieldOffset(8)]
		public int height;

		// if type == EventType.WindowClosing
		[FieldOffset(4)]
		public bool wantToQuit;

		// if type == EventType.WindowFocused
		[FieldOffset(4)]
		public bool isFocused;

		// if type == EventType.Key
		[FieldOffset(4)]
		public Key key;
		[FieldOffset(8)]
		public ButtonState keyState;

		// if type == EventType.MouseButton
		[FieldOffset(4)]
		public MouseButton button;
		[FieldOffset(8)]
		public ButtonState buttonState;

		// if type == EventType.MouseMoved
		[FieldOffset(4)]
		public int mouseX;
		[FieldOffset(8)]
		public int mouseY;

		// if type == EventType.MouseScrollWheelScrolled
		[FieldOffset(4)]
		public int scrolledDelta;
		#endregion
	}


	public class EventSystem
	{
		public ButtonState[] keys;
		public ButtonState[] buttons;

		public int[]	mousePosition;
		public int		mouseScrollWheelValue;

		public List<Event> eventQueue;


		public EventSystem()
		{
			keys		= new ButtonState[ (int)Key.Count ];
			buttons		= new ButtonState[ (int)MouseButton.Count ];

			mousePosition			= new int[2];
			mouseScrollWheelValue	= 0;

			eventQueue = new List<Event>();
		}


		public bool KeyPressed(Key key) => ( keys[ (int)key ] & ButtonState.Pressed ) == ButtonState.Pressed;
		public bool KeyReleased(Key key) => ( keys[ (int)key ] & ButtonState.Released ) == ButtonState.Released;
		public bool KeyClicked(Key key) => ( keys[ (int)key ] & ButtonState.Clicked ) == ButtonState.Clicked;

		public bool MouseButtonPressed(MouseButton button) => ( buttons[ (int)button ] & ButtonState.Pressed ) == ButtonState.Pressed;
		public bool MouseButtonReleased(MouseButton button) => ( buttons[ (int)button ] & ButtonState.Released ) == ButtonState.Released;
		public bool MouseButtonClicked(MouseButton button) => ( buttons[ (int)button ] & ButtonState.Clicked ) == ButtonState.Clicked;


		public void AddWindowResizeEvent(int width, int height)
		{
			Event e		= new Event();
			e.type		= Event.Type.WindowResized;
			e.width		= width;
			e.height	= height;

			eventQueue.Add(e);
		}

		public void AddWindowCloseEvent(bool wantToQuit)
		{
			Event e			= new Event();
			e.type			= Event.Type.WindowClosing;
			e.wantToQuit	= wantToQuit;

			eventQueue.Add(e);
		}

		public void AddWindowFocusEvent(bool isFocused)
		{
			Event e		= new Event();
			e.type		= Event.Type.WindowFocused;
			e.isFocused = isFocused;

			eventQueue.Add(e);
		}

		public void AddKeyEvent(Key key, ButtonState state)
		{
			Event e		= new Event();
			e.type		= Event.Type.Key;
			e.key		= key;
			e.keyState	= state;

			eventQueue.Add(e);
		}

		public void AddMouseButtonEvent(MouseButton button, ButtonState state)
		{
			Event e			= new Event();
			e.type			= Event.Type.MouseButton;
			e.button		= button;
			e.buttonState	= state;

			eventQueue.Add(e);
		}

		public void AddMouseMoveEvent(int x, int y)
		{
			Event e		= new Event();
			e.type		= Event.Type.MouseMoved;
			e.mouseX	= x;
			e.mouseY	= y;

			eventQueue.Add(e);
		}

		public void AddMouseScrollWheelScrollEvent(int scrolledDelta)
		{
			Event e			= new Event();
			e.type			= Event.Type.MouseScrollWheelScrolled;
			e.scrolledDelta	= scrolledDelta;

			eventQueue.Add(e);
		}
	}
}
