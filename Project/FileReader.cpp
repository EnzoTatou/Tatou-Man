#include "FileReader.hpp"

std::vector<std::string> readFile(const std::string _filePath)
{
	std::vector<std::string> lines;

	std::ifstream file(_filePath);
	if (!file.is_open())
	{
		std::cerr << "Could not open the file '" << _filePath << "'" << std::endl;
		std::vector<std::string> tempVector;
		return tempVector;
	}

	while (file.peek() != EOF)
	{
		std::string tempString;
		std::getline(file, tempString);
		lines.push_back(tempString);
	}

	file.close();

	return lines;
}