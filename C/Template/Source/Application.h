#pragma once

#include "Runtime.h"



Void OnAppInit(Void* userParam);
Void OnAppResize(SizeType width, SizeType height);
Void OnAppQuit(Bool wantToQuit);
Void OnAppFocus(Bool isFocused);

Void OnUpdate(RealType deltaTime);
Void OnRender(Void* RenderTarget);