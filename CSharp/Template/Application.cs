using Engine;
using Engine.Windows;



public unsafe class Application
{
	private static Runtime*		runtime;
	private static Window*		window;
	private static EventSystem*	eventSystem;


	public static void OnAppInit(void* userParam)
	{
		runtime		= (Runtime*)userParam;
		window		= &runtime->window;
		eventSystem	= &runtime->eventSystem;
	}

	public static void OnAppResize(int width, int height)
	{

	}

	public static void OnAppQuit(bool wantToQuit)
	{
		runtime->wantToQuit = wantToQuit;
	}

	public static void OnAppFocus(bool isFocused)
	{

	}


	public static void OnUpdate(float deltaTime)
	{
		if ( eventSystem->KeyClicked(Key.ESC) )
			runtime->wantToQuit = true;
	}

	public static void OnRender(IntPtr RenderTarget)
	{
		for( int y = 0; y < window->Height; y++ )
			for( int x = 0; x < window->Width; x++ )
			{
				uint* Target = (uint*)RenderTarget;

				uint* pixel = &Target[ window->Width * y + x ];

				byte b = 0;
				byte g = 0;
				byte r = 255;
				byte a = 0;

				*pixel = (uint)( ( b << 0 ) | ( g << 8 ) | ( r << 16 ) | ( a << 24 ) );
			}
	}
}