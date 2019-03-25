#pragma once
#include <optional>
#include "SDL2\include\SDL_rect.h"

struct ITexture
{
	virtual void Draw(const std::optional<SDL_Rect> & destination, const std::optional<SDL_Rect> & source = std::nullopt) const = 0;
	virtual ~ITexture() = default;
};
