#include "Application.h"



#pragma region Local
static Runtime*		runtime;
static Window*		window;
static EventSystem*	eventSystem;

static Serface RenderSerface;


static Asset loadedAsset;
#pragma endregion


Void OnAppInit(Void* userParam)
{
	runtime		= CAST(Runtime*, userParam);
	window		= &runtime->window;
	eventSystem	= &runtime->eventSystem;

	FMemory.Clear( &RenderSerface, sizeof(Serface) );

	// apply default config
	{
		loadedAsset.isLoaded = False;

		FEventSystem.AddKeyEvent(eventSystem, Key_O, ButtonState_Clicked);
	}
}

Void OnAppResize(SizeType width, SizeType height)
{
	FSerface.Destruct( &RenderSerface );
	RenderSerface = FSerface.Construct( width, height, sizeof(Color) );
}

Void OnAppQuit(Bool wantToQuit)
{
	runtime->wantToQuit = wantToQuit;
}

Void OnAppFocus(Bool isFocused)
{

}


Void OnUpdate(RealType deltaTime)
{
	if( FEventSystem.KeyClicked(eventSystem, Key_ESC) )
		runtime->wantToQuit = True;

	if ( FEventSystem.KeyClicked(eventSystem, Key_O) )
	{
		Char16 filename[512];
		if ( FFileDialog.Open( filename, sizeof(filename) / sizeof(Char16), L"(*.bmp)\0*.*\0", L"./", L"Open *.bmp", window->handle))
		{
			FAsset.Destruct( &loadedAsset );

			U16String u16Filename	= FU16String.Construct(filename);
			U8String path			= FU16String.ToU8String(&u16Filename);

			loadedAsset = FAsset.Construct( &path, AssetType_Bitmap );

			FU8String.Destruct( &path );
			FU16String.Destruct( &u16Filename );
		}
	}
}

Void OnRender(Void* RenderTarget)
{
	if ( !loadedAsset.isLoaded )
		return;

	// frame begin
	FSerface.Clear( &RenderSerface, &FColor.Black );

	// do your rendering work here(by updating RenderSerface)
	{
		Bitmap* bitmap = &loadedAsset.bitmap;

		SizeType width		= window->width;
		SizeType height		= window->height;
		SizeType centerX	= width / 2;
		SizeType centerY	= height / 2;

		RealType scale;
		{
			const RealType MaximumHorizontalScale	= CAST(RealType, width) / bitmap->width;
			const RealType MaximumVerticalScale		= CAST(RealType, height) / bitmap->height;

			scale = FMath.Minimum(MaximumHorizontalScale, MaximumVerticalScale);
		}

		SizeType imageWidth		= bitmap->width * scale;
		SizeType imageHeight	= bitmap->height * scale;

		Int32 xBegin	= centerX - imageWidth / 2;
		Int32 xEnd		= xBegin + imageWidth;
		Int32 yBegin	= centerY - imageHeight / 2;
		Int32 yEnd		= yBegin + imageHeight;

		for ( Int32 y = yBegin; y < yEnd; y++ )
			for ( Int32 x = xBegin; x < xEnd; x++ )
			{
				RealType u = CAST( RealType, x - xBegin ) / ( imageWidth - 1 );
				RealType v = CAST( RealType, y - yBegin ) / ( imageHeight - 1 );

				UInt32 pixel = FBitmap.GetPixel( bitmap, ( bitmap->width - 1 ) * u, ( bitmap->height - 1 ) * v );

				typedef struct { Byte b, g, r, a; } BGRA;
				BGRA* from	= CAST( BGRA*, &pixel );
				Color* to	= REINTERPRET_CAST( Color*, RenderSerface.buffer, RenderSerface.datatypeSize * ( width * y + x ) );

				to->r = from->r / 255.0;
				to->g = from->g / 255.0;
				to->b = from->b / 255.0;
				to->a = from->a / 255.0;
			}
	}

	// frame end
	{
		typedef struct { Byte b, g, r, a; } BGRA;


		for ( SizeType index = 0; index < RenderSerface.elementCount; index++ )
		{
			Color* from	= REINTERPRET_CAST( Color*, RenderSerface.buffer, RenderSerface.datatypeSize * index );
			BGRA* to	= REINTERPRET_CAST( BGRA*, RenderTarget, sizeof(BGRA) * index );

			to->b = FMath.Clamp01( from->b ) * 255;
			to->g = FMath.Clamp01( from->g ) * 255;
			to->r = FMath.Clamp01( from->r ) * 255;
			to->a = FMath.Clamp01( from->a ) * 255;
		}
	}
}
