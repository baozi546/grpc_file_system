#include "FileDetail.h"
#include "tools.h"
FileDetail::FileDetail(const std::string& path, const std::string& name, long long size)
	: _path(path),_name(name), _size(size)
{
	/*for (int i = 0; i < (_size + 1024 * 1024) / 4; i++)
	{
		_blocks.insert(i);
	}*/
	std::string location = path + "\\" + name;
	_md5 = tools::calculate_md5(location.c_str(),location.size());
}

const std::string& FileDetail::path() const
{
	return _path;
}

const std::string& FileDetail::name() const
{
	return _name;
}

const std::string& FileDetail::type() const
{
	return _name.substr(_name.rfind('.'));
}

const long long FileDetail::size() const
{
	return _size;
}

const int FileDetail::find_next() const
{
	if (_blocks.empty()) return -1;
	return *_blocks.begin();
}

const std::string& FileDetail::md5() const
{
	return _md5;
}

const std::string FileDetail::location() const
{
	return _path + "\\" + _name;
}
