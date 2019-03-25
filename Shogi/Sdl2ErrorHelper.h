#pragma once
#include "Logger.h"
#include <string_view>

class Sdl2ErrorHelper
{
public:
	static void CheckErrorCode(int zeroIsOkFromSdl2Function, std::string_view commentToError);
	static void CheckBoolResult(int trueIsOkFromSdl2Function, std::string_view commentToError);

	template<class Handle>
	static Handle* CheckHandle(Handle* handleFromSdl2Function, std::string_view commentToError)
	{
		return static_cast<Handle*>(CheckHandleImpl(handleFromSdl2Function, commentToError));
	}

private:
	static void GenerateSdl2Error(std::string_view commentToError);
	static void* CheckHandleImpl(void* handleFromSdl2Function, std::string_view commentToError);
};

