#pragma once
#include <string>
#include <filesystem>

struct ISystemInformation
{
	virtual const std::filesystem::path& GetExecutablePath() = 0;
	virtual const std::filesystem::path& GetExecutableDirectoryPath() = 0;
	virtual const std::string& GetExecutableName() = 0;
	virtual const std::string& GetExecutableNameWithoutExtension() = 0;
	virtual const std::string& GetNewLine() = 0;
	virtual ~ISystemInformation() = default;
};

class SystemInformation: public ISystemInformation
{
public:
	SystemInformation(int argc, char* args[]);
	const std::filesystem::path& GetExecutablePath();
	const std::filesystem::path& GetExecutableDirectoryPath();
	const std::string& GetExecutableName();
	const std::string& GetExecutableNameWithoutExtension();
	const std::string& GetNewLine();

private:
	void Check();
	void InitExecutablePath(int argc, char * args[]);
	void InitNewLine();

	const size_t MinPathSize = 5;
	std::filesystem::path _executablePath;
	std::filesystem::path _executableDirectoryPath;
	std::string _executableName;
	std::string _executableNameWithoutExtension;
	std::string _newLine;
};

