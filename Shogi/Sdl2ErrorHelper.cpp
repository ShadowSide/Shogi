#include "pch.h"
#include "SDL2/Include/SDL_error.h"
#include <string>
#include "Sdl2ErrorHelper.h"
using namespace std::string_literals;

void Sdl2ErrorHelper::CheckErrorCode(int zeroIsOkFromSdl2Function, std::string_view commentToError)
{
	if (zeroIsOkFromSdl2Function != 0)
		GenerateSdl2Error(commentToError);
}

void Sdl2ErrorHelper::CheckBoolResult(int trueIsOkFromSdl2Function, std::string_view commentToError)
{
	if (trueIsOkFromSdl2Function == 0)
		GenerateSdl2Error(commentToError);
}

void Sdl2ErrorHelper::GenerateSdl2Error(std::string_view commentToError)
{
	auto errorMsg = commentToError.empty() ? ""s : (std::string(commentToError) + ": ") + SDL_GetError();
	SDL_ClearError();
	Logger::WriteError(errorMsg);
	throw std::runtime_error(errorMsg);
}

void* Sdl2ErrorHelper::CheckHandleImpl(void* handleFromSdl2Function, std::string_view commentToError)
{
	if (handleFromSdl2Function == nullptr)
		GenerateSdl2Error(commentToError);
	return handleFromSdl2Function;
}
