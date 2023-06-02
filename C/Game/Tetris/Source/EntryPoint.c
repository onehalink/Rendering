#include "Application.h"

#include "BaseDefines.h"



Int32 EntryPoint()
{
	Runtime runtime;
	runtime.wantToQuit = False;

	EventSystem* eventSystem	= &runtime.eventSystem;
	*eventSystem				= FEventSystem.Construct(64);
	DynamicArray* eventQueue	= &eventSystem->eventQueue;

	Window* window	= &runtime.window;
	*window			= FWindow.Construct( L"Tetris", FrameWidth * 1.5, FrameHeight, L"Class Entry", NullPointer, eventSystem );

	GraphicDeviceInterface gdi = FGraphicDeviceInterface.Construct( window->handle );

	OnAppInit( &runtime );

	// main loop
	{
		Timer timer			= FTimer.Construct();
		RealType timestep	= 0;

		while ( !runtime.wantToQuit )
		{
			for ( SizeType index = 0; index < eventQueue->count; index++ )
			{
				Event* event = CAST( Event*, FDynamicArray.IndexAt(eventQueue, index) );

				switch ( event->type )
				{
				case EventType_WindowResized:
				{
					window->width	= event->width;
					window->height	= event->height;

					OnAppResize( event->width, event->height );
				}
					break;
				case EventType_WindowClosing:
					OnAppQuit( event->wantToQuit );
					break;
				case EventType_WindowFocused:
					OnAppFocus( event->isFocused );
					break;

				case EventType_Key:
					eventSystem->keys[ event->key ] |= event->keyState;
					break;

				case EventType_MouseButton:
					eventSystem->buttons[ event->button ] |= event->buttonState;
					break;
				case EventType_MouseMoved:
					eventSystem->mousePosition[0] = event->mouseX;
					eventSystem->mousePosition[1] = event->mouseY;
					break;

				case EventType_MouseScrollWheelScrolled:
					eventSystem->mouseScrollWheelScrolledValue += event->scrolledDelta;
					break;
				}
			}

			OnUpdate(timestep);
			FGraphicDeviceInterface.Present( &gdi, window->width, window->height, OnRender );

			// reset
			{
				FDynamicArray.Clear(eventQueue);

				// clear keys
				for ( SizeType index = 0; index < Key_Count; index++ )
					if (
						( eventSystem->keys[index] & ButtonState_Clicked ) ==
						ButtonState_Clicked
						)
						eventSystem->keys[index] &= ~ButtonState_Clicked;

				// clear buttons
				for ( SizeType index = 0; index < MouseButton_Count; index++ )
					if (
						( eventSystem->buttons[index] & ButtonState_Clicked ) ==
						ButtonState_Clicked
						)
						eventSystem->buttons[index] &= ~ButtonState_Clicked;
			}

			FWindow.Update(window);

			timestep = FTimer.Elapsed( &timer );
			FTimer.Reset( &timer );
		}
	}

	FGraphicDeviceInterface.Destruct( &gdi );
	FWindow.Destruct(window);
	FEventSystem.Destruct(eventSystem);

	return 0;
}


int main(int count, char** arguments)
{
	return EntryPoint();
}


#if defined(PLATFORM_WINDOWS)
#include <Windows.h>


int wWinMain(HINSTANCE current, HINSTANCE previous, PWSTR commandLine, int commandShow)
{
	return EntryPoint();
}
#endif