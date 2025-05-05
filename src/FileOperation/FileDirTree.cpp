#include "FileDirTree.h"
#include "tools.h"



FileDirTree::FileDirTree(const std::string& name) :dir_name(name)
{
}

FileDirTree::~FileDirTree()
{
}

bool FileDirTree::Create_dir(const std::string& name)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);

    if (name.empty()) {
		LOG_ERROR("Create dir " + name + " failed");
		return false;
	}

	if (m_dirs.contains(name)) {
		LOG_ERROR("Create dir " + name + " failed");
		return false;
	}

	std::shared_ptr<FileDirTree> dir = std::make_shared<FileDirTree>(name);
	m_dirs.insert({ name, dir });
	LOG_INFO("Create dir " + name);
	return true;
}

bool FileDirTree::Add_file(const FileDirTreeNode& node)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);
    m_file_info.insert({ node.file_name, node });
	return true;
}

bool FileDirTree::Rename_dir(const std::string& old_name, const std::string& new_name)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);

	if (old_name.empty() || new_name.empty()) {
		LOG_ERROR("Rename dir " + old_name + " failed");
		return false;
	}

	if (!m_dirs.contains(old_name) || m_dirs.contains(new_name)) {
		LOG_ERROR("Rename dir " + old_name + " failed");
		return false;
	}

	auto dir_ptr = m_dirs.at(old_name);

	dir_ptr->Modify_Dir_name(new_name);
    m_dirs.erase(old_name);
    m_dirs.insert({ new_name, dir_ptr });

	LOG_INFO("Rename dir " + old_name);
	return true;
}

bool FileDirTree::File_exist(const std::string& name, FileDirTreeNode& node)
{
	std::shared_lock<std::shared_mutex> lock(file_mutex);
    if (m_file_info.contains(name)) {
		node = m_file_info.at(name);
		return true;
	}
    return false;
}

bool FileDirTree::File_exist(const std::string& name)
{
	std::shared_lock<std::shared_mutex> lock(file_mutex);
	if (m_file_info.contains(name)) {
		return true;
	}
	return false;
}

bool FileDirTree::Remove_child(const std::string& name)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);
    if (m_dirs.contains(name)) {
		m_dirs.erase(name);
		return true;
	}
	return false;
}

bool FileDirTree::Remove_file(const std::string& name)
{
    std::unique_lock<std::shared_mutex> lock(file_mutex);
    if (m_file_info.contains(name)) {
		m_file_info.erase(name);
		return true;
	}
	return false;
}



bool FileDirTree::Rename_file(const std::string& old_name, const std::string& new_name)
{
	std::unique_lock<std::shared_mutex> lock(file_mutex);

	if (!(tools::Check_Filename(old_name) && tools::Check_Filename(new_name))) {
		LOG_WARNING("Rename file " + old_name + " failed");
		return false;
	}

	if (old_name.empty() || new_name.empty()) {
		LOG_ERROR("Rename dir " + old_name + " failed");
		return false;
	}

	if (!m_file_info.contains(old_name) || m_file_info.contains(new_name)) {
		LOG_ERROR("Rename dir " + old_name + " failed");
		return false;
	}

	auto file_ptr = m_file_info.at(old_name);

	m_file_info.erase(old_name);
	m_file_info.insert({ new_name, file_ptr });

	LOG_INFO("Rename file " + old_name);
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

std::vector<std::shared_ptr<FileDirTree>> FileDirTree::Get_child_list()
{
	std::shared_lock<std::shared_mutex> lock(file_mutex);
	std::vector<std::shared_ptr<FileDirTree>> child_list;
    for (auto& [key, value] : m_dirs) {
        child_list.push_back(value);
    }
    return child_list;
}

std::vector<FileDirTree::FileDirTreeNode> FileDirTree::Get_File_List()
{
	std::shared_lock<std::shared_mutex> lock(file_mutex);
	std::vector<FileDirTree::FileDirTreeNode> File_list;

	for (auto& [key, value] : m_dirs) {
		File_list.push_back({ "",key,FileDirTreeNode::FILE_TYPE::DIR });
	}

	for (auto& [key, value] : m_file_info){
        File_list.push_back(value);
	}
	return File_list;
}

void FileDirTree::Modify_Dir_name(const std::string& new_name)
{
    dir_name = new_name;
}
