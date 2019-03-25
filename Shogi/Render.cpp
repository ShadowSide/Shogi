#include "pch.h"
#include "Render.h"
#include "Sdl2ErrorHelper.h"

Render::Render(SDL_Renderer * sdlRenderer)
	: _renderer(sdlRenderer, SDL_DestroyRenderer)
{
	if (sdlRenderer == nullptr)
		throw std::logic_error("sdlRenderer is null");
	Sdl2ErrorHelper::CheckErrorCode(SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE), "Render::Render/SDL_SetRenderDrawColor");
	Sdl2ErrorHelper::CheckErrorCode(SDL_RenderClear(_renderer.get()), "Render::Render/SDL_RenderClear");
	Present();
}

void Render::DrawLine(const FloatRect & fromTo, const Color & rgba) const
{
	auto sdlFromTo = ToViewSpace(fromTo);
	Sdl2ErrorHelper::CheckErrorCode(SDL_SetRenderDrawColor(_renderer.get(), rgba.r, rgba.g, rgba.b, rgba.a), "Render::DrawLine/SDL_SetRenderDrawColor");
	Sdl2ErrorHelper::CheckErrorCode(SDL_RenderDrawLine(_renderer.get(), sdlFromTo->x, sdlFromTo->y, sdlFromTo->w, sdlFromTo->h), "Render::DrawLine/SDL_RenderDrawLine");
}

void Render::Draw(const std::optional<FloatRect>& destination, const std::optional<SDL_Rect>& source, const ITexture& texture) const
{
	auto sdlDestination = ToViewSpace(destination);
	texture.Draw(sdlDestination, source);
}

void Render::Present() const
{
	SDL_RenderPresent(_renderer.get());
}

const std::shared_ptr<SDL_Renderer>& Render::Renderer() const
{
	return _renderer;
}

FloatRect Render::ClampViewSpace(FloatRect rect) const
{
	if (rect.x1 < 0.f)
		rect.x1 = 0.f;
	if (rect.x2 < 0.f)
		rect.x2 = 0.f;
	if (rect.y1 < 0.f)
		rect.y1 = 0.f;
	if (rect.y2 < 0.f)
		rect.y2 = 0.f;

	if (rect.x1 > 1.f)
		rect.x1 = 1.f;
	if (rect.x2 > 1.f)
		rect.x2 = 1.f;
	if (rect.y1 > 1.f)
		rect.y1 = 1.f;
	if (rect.y2 > 1.f)
		rect.y2 = 1.f;
	return rect;
}

SDL_Rect Render::ClampViewSpace(SDL_Rect rect, const SDL_Rect& outputClamp) const
{
	if (rect.x < outputClamp.x)
		rect.x = outputClamp.x;
	if (rect.w < outputClamp.x)
		rect.w = outputClamp.x;
	if (rect.y < outputClamp.y)
		rect.y = outputClamp.y;
	if (rect.h < outputClamp.y)
		rect.h = outputClamp.y;

	if (rect.x > outputClamp.w)
		rect.x = outputClamp.w;
	if (rect.w > outputClamp.w)
		rect.w = outputClamp.w;
	if (rect.y > outputClamp.h)
		rect.y = outputClamp.h;
	if (rect.h > outputClamp.h)
		rect.h = outputClamp.h;
	return rect;
}

std::optional<SDL_Rect> Render::ToViewSpace(const std::optional<FloatRect>& rect) const
{
	if (!rect)
		return std::nullopt;
	auto rect_ = ClampViewSpace(*rect);
	SDL_Rect outputClamp = {};
	Sdl2ErrorHelper::CheckErrorCode(SDL_GetRendererOutputSize(_renderer.get(), &(outputClamp.w), &(outputClamp.h)), "Render::ToViewSpace/SDL_GetRendererOutputSize");
	outputClamp.w = outputClamp.w - 1;
	outputClamp.h = outputClamp.h - 1;
	SDL_Rect result 
	{
		static_cast<int>(rect_.x1*outputClamp.w),
		static_cast<int>(rect_.y1*outputClamp.h),
		static_cast<int>(rect_.x2*outputClamp.w),
		static_cast<int>(rect_.y2*outputClamp.h),
	};
	return ClampViewSpace(result, outputClamp);
}
