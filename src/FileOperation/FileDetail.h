#pragma once
#include <set>
#include <string>
#include <mutex>
#include <map>

struct FileMeteData {
	std::string _file_id;
	std::string _owner;
	int acctual_block_id;
	std::string _name;
	std::string _md5;
	long long _size;
};

class FileDetail {
public:
	FileDetail(std::shared_ptr<FileMeteData> file);
	
	bool modify_block(int block,int size);
	const std::map<int, std::pair<int, bool>>  blocks();
	bool set_merge();
	std::shared_ptr<FileMeteData> get_mete_data();

private:
	std::shared_ptr<FileMeteData> _metedata;
	std::map<int, std::pair<int, bool>>  _blocks;//´æ´¢ÎÄ¼þ¿é
	std::mutex _mutex;
	bool _merge_status = false;
};
