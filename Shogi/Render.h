#pragma once
#include "Handle.h"
#include <SDL2\include\SDL_render.h>
#include "FloatRect.h"
#include "Color.h"
#include "Texture.h"

class Render
{
public:
	explicit Render(SDL_Renderer* sdlRender);

	void DrawLine(const FloatRect& fromTo, const Color& rgba) const;
	//void FillRect(const FloatRect& rect, const Color& rgba) const;
	void Draw(const std::optional<FloatRect>& destination, const std::optional<SDL_Rect>& source, const ITexture& texture) const;
	void Present() const;
	const std::shared_ptr<SDL_Renderer>& Renderer() const;

private:
	std::optional<SDL_Rect> ToViewSpace(const std::optional<FloatRect>& rect) const;
	FloatRect ClampViewSpace(FloatRect rect) const;
	SDL_Rect ClampViewSpace(SDL_Rect rect, const SDL_Rect& outputClamp) const;
	Handle<SDL_Renderer> _renderer;
};

