#include "Button.h"



static Void Render(Serface* serface, EventSystem* attactedEventSystem, const Char8* inAsciiString, const Vector2* position, const Color* foreground, const Color* background, SizeType borderWidth, const Color* borderColor, FButtonOnPressedCallback OnPressed, FButtonOnClickedCallback OnClicked)
{
	//ASSERT( serface->datatypeSize == sizeof(Color) );


	const SizeType InAsciiCount = FUnicode.GetUTF8ElementCount(inAsciiString, 0x00);

	Color normal		= *background;
	Color highlighted	= FColor.MultiplyCS(&normal, 0.8F);
	Color pressed		= FColor.MultiplyCS(&normal, 0.5F);

	Color current		= normal;

	// Used to represent renderable area
	Int32 left, right, bottom, top;

	Bool isHover = False;
	{
		left	= position->x;
		right	= left + FAsciiGlyphInfo.Width * (InAsciiCount + 2);
		bottom	= position->y;
		top		= bottom + FAsciiGlyphInfo.Height * (1 + 0.5);

		Int32 mx = attactedEventSystem->mousePosition[0];
		Int32 my = attactedEventSystem->mousePosition[1];
		
		if ( 
			mx >= left && mx < right &&
			my >= bottom && my < top
			)
			isHover = True;
	}

	// test bound
	if (
		left < 0 || left >= serface->width ||
		right < 0 || right >= serface->width ||
		bottom < 0 || bottom >= serface->height ||
		top < 0 || top >= serface->height
		)
		return;

	if (isHover)
	{
		current = highlighted;

		if ( FEventSystem.MouseButtonPressed(attactedEventSystem, MouseButton_Left) )
		{
			current = pressed;

			if (OnPressed)
				OnPressed();
		}

		if ( OnClicked && FEventSystem.MouseButtonClicked(attactedEventSystem, MouseButton_Left) )
			OnClicked();
	}
	else
		current = normal;

	// draw background
	for(SizeType y = bottom; y < top; y++)
		for (SizeType x = left; x < right; x++)
			FSerface.SetValue(serface, x, y, &current);

	// draw border
	{
		// left side
		for(SizeType x = left; x < left + borderWidth; x++)
			for(SizeType y = bottom; y < top; y++)
				FSerface.SetValue(serface, x, y, borderColor);

		// right side
		for (SizeType x = right - borderWidth; x < right; x++)
			for (SizeType y = bottom; y < top; y++)
				FSerface.SetValue(serface, x, y, borderColor);

		// bottom side
		for(SizeType y = bottom; y < bottom + borderWidth; y++)
			for (SizeType x = left; x < right; x++)
				FSerface.SetValue(serface, x, y, borderColor);

		// top side
		for (SizeType y = top - borderWidth; y < top; y++)
			for (SizeType x = left; x < right; x++)
				FSerface.SetValue(serface, x, y, borderColor);
	}

	// draw text
	{
		Vector2 position;
		position.x = left + FAsciiGlyphInfo.Width;
		position.y = bottom + FAsciiGlyphInfo.Height * 0.25;

		FText.Render(serface, inAsciiString, &position, foreground);
	}
}


struct FButton FButton =
{
	Render,
};
