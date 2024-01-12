#include "FileUtils.h"
#include <fstream>
#include <sstream>
#include <iostream>
std::string FileUtils::loadFile(std::string path) {
	std::ifstream shaderFile(path);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	return buffer.str();
}