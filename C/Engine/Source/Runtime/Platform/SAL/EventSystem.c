#include "EventSystem.h"



static EventSystem Construct(SizeType eventQueueCapacity)
{
	EventSystem ret;
	FMemory.Clear( &ret, sizeof(EventSystem) );
	ret.eventQueue = FDynamicArray.Construct( eventQueueCapacity, sizeof(Event) );

	return ret;
}

static Void Destruct(EventSystem* instance)
{
	if ( !instance )
		return;

	FDynamicArray.Destruct( &instance->eventQueue );
}

static Bool KeyPressed(const EventSystem* instance, Key key)
{
	return ( instance->keys[key] & ButtonState_Pressed ) == ButtonState_Pressed;
}

static Bool KeyReleased(const EventSystem* instance, Key key)
{
	return ( instance->keys[key] & ButtonState_Released ) == ButtonState_Pressed;
}

static Bool KeyClicked(const EventSystem* instance, Key key)
{
	return ( instance->keys[key] & ButtonState_Clicked ) == ButtonState_Clicked;
}

static Bool MouseButtonPressed(const EventSystem* instance, MouseButton button)
{
	return ( instance->buttons[button] & ButtonState_Pressed ) == ButtonState_Pressed;
}

static Bool MouseButtonReleased(const EventSystem* instance, MouseButton button)
{
	return ( instance->buttons[button] & ButtonState_Released ) == ButtonState_Released;
}

static Bool MouseButtonClicked(const EventSystem* instance, MouseButton button)
{
	return ( instance->buttons[button] & ButtonState_Clicked ) == ButtonState_Clicked;
}

static Void AddWindowResizeEvent(EventSystem* instance, SizeType width, SizeType height)
{
	Event event;
	event.type		= EventType_WindowResized;
	event.width		= width;
	event.height	= height;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddWindowCloseEvent(EventSystem* instance, Bool wantToQuit)
{
	Event event;
	event.type			= EventType_WindowClosing;
	event.wantToQuit	= wantToQuit;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddWindowFocusEvent(EventSystem* instance, Bool isFocused)
{
	Event event;
	event.type		= EventType_WindowFocused;
	event.isFocused	= isFocused;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddKeyEvent(EventSystem* instance, Key key, ButtonState state)
{
	Event event;
	event.type		= EventType_Key;
	event.key		= key;
	event.keyState	= state;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddMouseButtonEvent(EventSystem* instance, MouseButton button, ButtonState state)
{
	Event event;
	event.type			= EventType_MouseButton;
	event.button		= button;
	event.buttonState	= state;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddMouseMoveEvent(EventSystem* instance, Int32 x, Int32 y)
{
	Event event;
	event.type		= EventType_MouseMoved;
	event.mouseX	= x;
	event.mouseY	= y;

	FDynamicArray.Add( &instance->eventQueue, &event );
}

static Void AddMouseScrollWheelScrollEvent(EventSystem* instance, Int32 scrolledDelta)
{
	Event event;
	event.type			= EventType_MouseScrollWheelScrolled;
	event.scrolledDelta	= scrolledDelta;

	FDynamicArray.Add( &instance->eventQueue, &event );
}


struct FEventSystem FEventSystem = 
{
	Construct,
	Destruct,
	KeyPressed,
	KeyReleased,
	KeyClicked,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseButtonClicked,
	AddWindowResizeEvent,
	AddWindowCloseEvent,
	AddWindowFocusEvent,
	AddKeyEvent,
	AddMouseButtonEvent,
	AddMouseMoveEvent,
	AddMouseScrollWheelScrollEvent,
};
