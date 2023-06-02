#pragma once

#include "../../Core.h"

#include "../SAL/EventSystem.h"



typedef struct
{
	Void*		handle;		// A native Windows window handle that will be used to indicate which window it is on desktop
	SizeType	width;		// The width of client area of Windows window
	SizeType	height;		// The height of client area of Windows window

	const Char16* className;
}
Window;


typedef Int64(*FWindowProcedureCallback)(Void* handle, UInt32 message, UInt64 wParam, Int64 lParam);

struct FWindow
{
	Window(*Construct)(const Char16* title, SizeType width, SizeType height, const Char16* className, FWindowProcedureCallback Fn, Void* userParam);
	Void(*Destruct)(Window* instance);


	// Poll events from OS
	Void(*Update)(Window* instance);
};

extern ENGINE_API struct FWindow FWindow;