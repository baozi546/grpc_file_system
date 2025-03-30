#include "FileDirTree.h"
#include "tools.h"

FileDirTree::FileDirTree()
{
}

FileDirTree::~FileDirTree()
{
}

bool FileDirTree::Create_dir(const std::string& name , const std::string& parent_path)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);
    if (m_dirs.contains(name)) {
		return false;
	}
	if (!std::filesystem::create_directory(parent_path + "\\" + name)) {
		LOG_ERROR("Create dir " + name + " failed");
		return false;
	};
	std::shared_ptr<FileDirTree> dir = std::make_shared<FileDirTree>();
    m_dirs.insert({ name, dir });
    LOG_INFO("Create dir " + name);
	return true;
}

std::shared_ptr<FileDirTree> FileDirTree::Get_child(const std::string& name)
{
	std::shared_lock<std::shared_mutex> lock(file_mutex);
	if (!m_dirs.contains(name)) {
		return nullptr;
	}
	return m_dirs.at(name);
}
