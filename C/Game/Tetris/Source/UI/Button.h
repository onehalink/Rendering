#pragma once

#include "Text.h"



typedef Void(*FButtonOnPressedCallback)();
typedef Void(*FButtonOnClickedCallback)();


struct FButton
{
	Void(*Render)(Serface* serface, EventSystem* attactedEventSystem, const Char8* inAsciiString, const Vector2* position, const Color* foreground, const Color* background, SizeType borderWidth, const Color* borderColor, FButtonOnPressedCallback OnPressed, FButtonOnClickedCallback OnClicked);
};

extern ENGINE_API struct FButton FButton;