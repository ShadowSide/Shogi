#include "pch.h"
#include "AppLoop.h"
#include "Locator.h"
#include "SystemInformation.h"
#include "Logger.h"
#include "Sdl2ErrorHelper.h"
#include "SDL2/include/SDL.h"
#include "Render.h"

AppLoop::AppLoop(int argc, char* args[])
{
	Locator::Init();
	Locator::RegisterInstance<ISystemInformation>(std::make_shared<SystemInformation>(argc, args));
	Logger::Init();
	InitSdl2();
}

void AppLoop::Execute()
{
	while (true)
	{
		SDL_Event sdlEvent {};
		Sdl2ErrorHelper::CheckBoolResult(SDL_WaitEvent(&sdlEvent), "SDL_WaitEvent");
		if (sdlEvent.type == SDL_QUIT)
			break;
		Update(sdlEvent);
		Draw();
	}
}

void AppLoop::Update(SDL_Event& sdlEvent)
{
}

void AppLoop::Draw()
{
}

AppLoop::~AppLoop()
{
	Locator::Close();
	SDL_Quit();
	_window.reset();
	Logger::Close();
}

void AppLoop::InitSdl2()
{
	Sdl2ErrorHelper::CheckErrorCode(SDL_Init(SDL_INIT_VIDEO), "SDL_Init");
	SDL_Window* wnd;
	SDL_Renderer* rnd;
	Sdl2ErrorHelper::CheckErrorCode(SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE, &wnd, &rnd), "SDL_CreateWindowAndRenderer");
	_window = Handle<SDL_Window>(wnd, SDL_DestroyWindow);
	Locator::RegisterInstance<Render>(std::make_shared<Render>(rnd));
}
