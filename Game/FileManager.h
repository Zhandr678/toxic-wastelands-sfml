#pragma once
#include <filesystem>
#include <string>

class FileManager
{
private:
	std::string solution_dir;
public:
	FileManager() = delete;
	FileManager(const FileManager& other) = delete;
	FileManager& operator =(const FileManager& other) = delete;
	FileManager(char** argv);

	std::string solution_directory();
	std::string maps_directory();
	std::string texture_directory();
};

