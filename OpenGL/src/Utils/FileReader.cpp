#include "FileReader.h"

#include <fstream>
#include <sstream>

std::string FileReader::ReadFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;

	buffer << file.rdbuf();

	file.close();

	return buffer.str();
}
