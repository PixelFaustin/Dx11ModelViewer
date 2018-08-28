#pragma once

#include "Canvas.h"

class Application
{
public:
	Application(Canvas* _Canvas);
	virtual ~Application();

	virtual bool Initialize() = 0;

	virtual void Update(float DeltaTime) = 0;
	virtual void Render(Renderer* _Renderer) = 0;

	virtual bool OnRun(float DeltaTime) = 0;
protected:
	Canvas* mCanvas;

};

