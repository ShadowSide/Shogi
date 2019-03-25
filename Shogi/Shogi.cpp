// Shogi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SDL2/include/SDL.h>
#include <iostream>
#include <stdio.h>
#include "AppLoop.h"

int main(int argc, char* args[]) {
	AppLoop app(argc, args);
	app.Execute();
	/*
	#define SCREEN_WIDTH 640
	#define SCREEN_HEIGHT 480

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* screenSurface = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}*/
	/*SDL_CreateWindowAndRenderer(
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN,
		&window,
		&renderer);*/
	/*window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == nullptr || renderer == nullptr) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	auto a = SDL_LoadBMP("C:\\Sergey\\Projects\\Shogi\\Debug\\levelup_shogi_inpos.bmp");
	if (a == NULL) {
		fprintf(stderr, "could not load bmp: %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetColorKey(a, SDL_TRUE, SDL_MapRGB(a->format, 0xDD, 0xDD, 0xDD));
	SDL_BlitScaled(a, &SDL_Rect{ 100,100,100,100 }, screenSurface, &SDL_Rect{ 10,10,100,100 });
	SDL_SetRenderDrawColor(renderer, 100, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 10, 10, 300, 300);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 50;
	rectangle.h = 50;
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	 SDL_PumpEvents
	SDL_DestroyWindow(window);
	SDL_Quit();*/
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
