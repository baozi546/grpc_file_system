#include "FileOperation.h"


int FileOperation::FileWrite(std::shared_ptr<FileDetail> detail)
{
	return 1;
}

int FileOperation::FileRead(const FileDetail&, std::vector<char>& buffer)
{
	return 1;
}
int FileOperation::FileCreate(const FileDetail&) 
{
	return 1;
};