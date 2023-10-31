#include "FileManager.h"

FileManager::FileManager(char** argv)
{
	solution_dir = std::filesystem::path(argv[0]).parent_path().string();
	solution_dir = solution_dir.substr(0, solution_dir.find_last_of("/\\"));
	solution_dir = solution_dir.substr(0, solution_dir.find_last_of("/\\"));
}

std::string FileManager::solution_directory()
{
	return solution_dir;
}

std::string FileManager::maps_directory()
{
	return solution_dir + "/maps";
}

std::string FileManager::texture_directory()
{
	return solution_dir + "/Textures";
}
