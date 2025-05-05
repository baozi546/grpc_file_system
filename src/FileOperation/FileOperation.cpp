#include "FileOperation.h"
#include <iostream>
#include <fstream>
#include "tools.h"

int FileOperation::FileWrite(const std::string& name ,const std::string& buffer ,const std::string& root_path)
{
	try {
		std::filesystem::create_directories(tools::StringToWString(root_path));
		std::ofstream out(tools::StringToWString(root_path + "\\" + name), std::ios::out | std::ios::binary);
		if (!out.is_open()) {
			return 0;
		}
		out.write(buffer.c_str(), buffer.size());
		return 1;
	}
	catch (...) {
		return -1;
	}
	return 0;
}

int FileOperation::FileRead(const std::string& name,std::string& buffer ,const std::string& root_path)
{
	try {
		std::ifstream in(tools::StringToWString(root_path + "\\" + name), std::ios::out | std::ios::binary);
		if (!in.is_open()) {
			return 0;
		}
		std::string content((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
		buffer = std::move(content);
		return 1;
	}
	catch (...) {
		return -1;
	}
	return 0;
}
int FileOperation::FileCreate(const std::string& name, const std::string& path)

{
	return 1;
};