#pragma once

#include <map>
#include <string>
#include <memory>
#include <atomic>
#include <vector>
#include <mutex>
#include <shared_mutex>
class FileDirTree {//虚拟目录

public:
	enum Modify_LEVEL
	{
		NONE = 0,
		CREATE_DIR = 1 << 0,
		ADD_DIR = 1 << 1,
		MODIFY_DIR = 1 << 2,
		DELETE_DIR = 1 << 3
	};
	struct FileDirTreeNode
	{
		enum FILE_TYPE {
			DIR = 0,
			FILE = 1
		};
		std::string file_id;//文件专属id
		std::string file_name;
		FILE_TYPE type;
	};
	FileDirTree(const std::string& name);
	~FileDirTree();
	bool Create_dir(const std::string& name);
	bool Add_file(const FileDirTreeNode& node);
	bool Rename_dir(const std::string& old_name, const std::string& new_name);
	bool Rename_file(const std::string& old_name, const std::string& new_name);
	bool File_exist(const std::string& name, FileDirTreeNode& node);
	bool File_exist(const std::string& name);
	bool Remove_child(const std::string& name);
	bool Remove_file(const std::string& name);
	std::shared_ptr<FileDirTree> Get_child(const std::string& name);
	std::vector<std::shared_ptr<FileDirTree>> Get_child_list();
	std::vector<FileDirTreeNode> Get_File_List();

	void Modify_Dir_name(const std::string& new_name);

	std::string Dump_Config();
private:

	std::map<std::string, std::shared_ptr<FileDirTree>> m_dirs;//只存放目录
	std::map<std::string, FileDirTreeNode> m_file_info; //第一个为文件名, 第二个为文件信息
	std::shared_mutex file_mutex;
	std::string dir_name;
};