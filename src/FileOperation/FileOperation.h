#pragma once
#include "FileDetail.h"
#include <vector>
#include <memory>

namespace FileOperation {

	int FileWrite(std::shared_ptr<FileDetail>);

	int FileRead(const FileDetail&,std::vector<char>& buffer);

	int FileCreate(const FileDetail&);

};