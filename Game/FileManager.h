#pragma once
#include <string>

class FileManager
{
private:

public:
	FileManager() = delete;
	FileManager(const FileManager& other) = delete;
	FileManager(char** argv);
	std::string solution_directory();
	std::string maps_directory();
	std::string texture_directory();
};

