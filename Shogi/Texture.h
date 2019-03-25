#pragma once
#include <optional>
#include <string_view>
#include "Handle.h"
#include "Color.h"
#include "FloatRect.h"
#include "ITexture.h"
#include "SDL2\include\SDL_Render.h"

class Texture: public ITexture
{
public:
	explicit Texture(std::string_view fileName, const std::optional<Color>& colorKey = std::nullopt);
	void Draw(const std::optional<SDL_Rect> & destination, const std::optional<SDL_Rect> & source = std::nullopt) const;
	//Handle<SDL_Texture> HandleValue() const;

private:
	static Handle<SDL_Texture> LoadTexture(std::string_view fileName, const std::optional<Color>& colorKey);

	Handle<SDL_Texture> _texture;
	//size_t _width, _height;
};

