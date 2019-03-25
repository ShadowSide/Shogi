#pragma once
#include "SDL2\include\SDL_events.h"
#include "Handle.h"

class AppLoop
{
public:
	AppLoop(int argc, char* args[]);
	void Execute();
	~AppLoop();
	void Update(SDL_Event& sdlEvent);
	void Draw();

private:
	void InitSdl2();
	Handle<SDL_Window> _window;
};

