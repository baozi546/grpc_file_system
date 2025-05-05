#pragma once
#include "FileDetail.h"
#include <vector>
#include <memory>

namespace FileOperation {

	int FileWrite(const std::string& name,const std::string& value , const std::string& root_path);

	int FileRead(const std::string& name, std::string& buffer , const std::string& root_path);

	int FileCreate(const std::string&name , const std::string& path);

};