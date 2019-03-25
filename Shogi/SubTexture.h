#pragma once
#include "Handle.h"
#include "Color.h"
#include "FloatRect.h"
#include "ITexture.h"
#include "Texture.h"
#include "SDL2\include\SDL_Render.h"

class SubTexture : public ITexture
{
public:
	explicit SubTexture(const Texture& texture, const SDL_Rect& source);
	void Draw(const std::optional<SDL_Rect> & destination, const std::optional<SDL_Rect> & source = std::nullopt) const;

private:
	Texture _texture;
	//size_t _width, _height;
	SDL_Rect _texureSource;
};