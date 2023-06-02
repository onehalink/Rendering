// See https://aka.ms/new-console-template for more information
using Engine;
using Engine.Windows;



using static Application;


unsafe
{
	var runtime			= new Runtime();
	runtime.wantToQuit	= false;

	var eventSystem	= &runtime.eventSystem;
	*eventSystem	= new EventSystem();

	var window = &runtime.window;
	*window = new Window( "Template(C#)", 1600, 960, new IntPtr(eventSystem) );

	var gdi = new GraphicDeviceInterface( window->Handle );

	OnAppInit( &runtime );

	// main loop
	{
		var timer		= new Engine.Timer();
		float timestep	= 0;

		while( !runtime.wantToQuit )
		{
			timestep = timer.Elapsed();
			timer.Reset();

			OnUpdate(timestep);
			gdi.Present( window->Width, window->Height, OnRender );

			// reset
			{
				eventSystem->eventQueue.Clear();

				// clear keys
				for ( int index = 0; index < (int)Key.Count; index++ )
					if (
						( eventSystem->keys[index] & ButtonState.Clicked ) ==
						ButtonState.Clicked
						)
						eventSystem->keys[index] &= ~ButtonState.Clicked;

				// clear mouse buttons
				for ( int index = 0; index < (int)MouseButton.Count; index++ )
					if (
						( eventSystem->buttons[index] & ButtonState.Clicked ) ==
						ButtonState.Clicked
						)
						eventSystem->buttons[index] &= ~ButtonState.Clicked;
			}

			window->Update();
			foreach ( var e in eventSystem->eventQueue )
				switch( e.type )
				{
					case Event.Type.WindowResized:
						OnAppResize( e.width, e.height );

						window->Width	= e.width;
						window->Height	= e.height;

						Console.WriteLine($"Size: {e.width}x{e.height}");
						break;
					case Event.Type.WindowClosing:
						OnAppQuit( e.wantToQuit );
						break;
					case Event.Type.WindowFocused:
						OnAppFocus( e.isFocused );
						break;

					case Event.Type.Key:
						eventSystem->keys[ (int)e.key ] |= e.keyState;
						break;

					case Event.Type.MouseButton:
						eventSystem->buttons[ (int)e.button ] |= e.buttonState;
						break;
					case Event.Type.MouseMoved:
						eventSystem->mousePosition[0] = e.mouseX;
						eventSystem->mousePosition[1] = e.mouseY;
						break;
					case Event.Type.MouseScrollWheelScrolled:
						eventSystem->mouseScrollWheelValue += e.scrolledDelta;
						break;
				}
		}
	}
}