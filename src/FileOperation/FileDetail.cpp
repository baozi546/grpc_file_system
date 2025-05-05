#include "FileDetail.h"
#include "tools.h"
#include "ThreadPool.h"
#include "FileOperation.h"
FileDetail::FileDetail(std::shared_ptr<FileMeteData> metedata): _metedata(metedata)
{
	uint64_t block_size = metedata->_size;
	int count = 0;
	while (block_size > 0) {
		int size = block_size > BLOCK_SIZE ? BLOCK_SIZE : block_size;
		_blocks.insert(std::make_pair(count, std::make_pair(size, false)));
		block_size -= size;
		count++;
	}

}

bool FileDetail::modify_block(int block ,int size)
{
	std::lock_guard<std::mutex> lock(_mutex);
	auto it = _blocks.find(block);
	if (it == _blocks.end() || it->second.second == true || size != it->second.first) {
		return false;
	}
	it->second.second = true;
	return true;
}

const std::map<int, std::pair<int, bool>>  FileDetail::blocks()
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _blocks;
}

bool FileDetail::set_merge()
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_merge_status) {
		return false;
	}
	for (const auto& [key, value] : _blocks) {
        if (value.second == false) {
            return false;
        }
	}
	_merge_status = true;
	return true;
}


std::shared_ptr<FileMeteData> FileDetail::get_mete_data()
{
	return _metedata;
}



