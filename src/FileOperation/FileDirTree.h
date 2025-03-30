#pragma once

#include <map>
#include <string>
#include <memory>
#include <atomic>
#include <vector>
#include <mutex>
#include <shared_mutex>
class FileDirTree {//����Ŀ¼

public:
	enum Modify_LEVEL
	{
		NONE = 0,
		CREATE = 1 << 0,
		ADD = 1 << 1,
		MODIFY = 1 << 2,
		DELETE = 1 << 3
	};
	struct FileDirTreeNode
	{
		std::string file_id;
		std::string file_name;
		std::string owner;
		uint64_t create_time;
		uint64_t modify_time;
	};
	FileDirTree();
    ~FileDirTree();
	bool Create_dir(const std::string& name, const std::string& parent_path);
	bool Add_file(const std::string file_name,std::string &owner);
	bool Remove_child(const std::string& name);
	bool Remove_file(const std::string& name);
	bool Find_file(const std::string& name);
	bool Modify_file(const std::string& name,std::string &owner);
	std::shared_ptr<FileDirTree> Get_child(const std::string& name);

	std::string Dump_Config();
private:
	
	 std::map<std::string, std::shared_ptr<FileDirTree>> m_dirs;//ֻ���Ŀ¼
	 std::map<std::string, FileDirTreeNode> m_file_info; //��һ��Ϊ�ļ�ר��ID, �ڶ���Ϊ�ļ���Ϣ
	 std::shared_mutex file_mutex;

     std::atomic<Modify_LEVEL> Dir_Level = NONE;
}; 