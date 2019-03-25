#pragma once
#include "SDL2/include/SDL_log.h"
#include <string_view>
#include <string>
#include <fstream>
#include "SystemInformation.h"

class Logger 
{
public:
	static void Init();
	static void AttachLogFromSdl2Log();

	static void WriteTrace(std::string_view msg);
	static void WriteInfo(std::string_view msg);
	static void WriteWarn(std::string_view msg);
	static void WriteError(std::string_view msg);

	static void WriteTrace(const std::exception& msg);
	static void WriteInfo(const std::exception& msg);
	static void WriteWarn(const std::exception& msg);
	static void WriteError(const std::exception& msg);

	static void Close();

private:
	static void Check();

	static void WriteLog(std::string_view msg);
	static std::string GetInformationAndFormatLog(std::string_view categoryName, std::string_view msg);
	static std::string GetInformationAndFormatLog(int category, SDL_LogPriority priority, std::string_view msg);
	static std::string GetCommonInformationAndFormatLog(std::string_view msg);
	static void WriteLogSdl2(void* userdata, int category, SDL_LogPriority priority, const char* message);

	static std::string GetSdl2CategoryName(int category);
	static std::string GetSdl2PriorityName(SDL_LogPriority priority);

	static std::fstream _file;
};

