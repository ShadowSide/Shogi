#include "pch.h"
#include "SubTexture.h"
#include "Locator.h"
#include "Render.h"
#include "Sdl2ErrorHelper.h"
#include "OptionalPtrHelper.h"

SubTexture::SubTexture(const Texture& texture, const SDL_Rect& source):
	_texture(texture),
	_texureSource(source)
{}

void SubTexture::Draw(const std::optional<SDL_Rect> & destination, const std::optional<SDL_Rect> & source) const
{
	if (source)
		throw std::invalid_argument("Not implemented not null source argument for " __FUNCSIG__);
	else
		_texture.Draw(destination, _texureSource);
}
