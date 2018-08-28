#include "stdafx.h"
#include "Application.h"

Application::Application(Canvas* _Canvas)
	: mCanvas(_Canvas)
{

}

Application::~Application()
{
	delete mCanvas;
}
