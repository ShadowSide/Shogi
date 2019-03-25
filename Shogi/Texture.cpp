#include "pch.h"
#include "SDL2/include/SDL_Surface.h"
#include "SDL2/include/SDL_Render.h"
#include "Locator.h"
#include "Texture.h"
#include "Render.h"
#include "SystemInformation.h"
#include "Sdl2ErrorHelper.h"
#include "OptionalPtrHelper.h"

Texture::Texture(std::string_view fileName, const std::optional<Color>& colorKey):
	_texture(LoadTexture(fileName, colorKey))
{}

Handle<SDL_Texture> Texture::LoadTexture(std::string_view fileName, const std::optional<Color>& colorKey)
{
	auto path = (Locator::Resolve<ISystemInformation>()->GetExecutableDirectoryPath() / fileName).string();
	Handle<SDL_Surface> surface(Sdl2ErrorHelper::CheckHandle(SDL_LoadBMP(path.c_str()), "Texture::Texture/SDL_LoadBMP"), SDL_FreeSurface);
	//Handle<SDL_Surface> surface2 = SDL_DisplayFormat(surface.get());
	if (colorKey)
		Sdl2ErrorHelper::CheckErrorCode(SDL_SetColorKey(surface.get(), SDL_TRUE, SDL_MapRGB(surface->format, colorKey->r, colorKey->g, colorKey->b)), "Texture::Texture/SDL_SetColorKey");
	/*_width = surface->w;
	_height = surface->h;*/
	auto&& renderer = Locator::Resolve<Render>()->Renderer();
	Handle<SDL_Texture> texture(
		Sdl2ErrorHelper::CheckHandle(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), "Texture::Texture/SDL_CreateTextureFromSurface"), SDL_DestroyTexture);
}

void Texture::Draw(const std::optional<SDL_Rect> & destination, const std::optional<SDL_Rect> & source) const
{
	auto&& renderer = Locator::Resolve<Render>()->Renderer();
	Sdl2ErrorHelper::CheckErrorCode(
		SDL_RenderCopy(
			renderer.get(), 
			_texture.get(), 
			OptionalPtrHelper::GetOrNull(source), 
			OptionalPtrHelper::GetOrNull(destination)), 
		"Texture::Draw/SDL_RenderCopy");
}

/*Handle<SDL_Texture> Texture::HandleValue() const
{
	return _texture;
}*/
