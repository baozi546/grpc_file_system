#pragma once
#include <set>
#include <string>
class FileDetail {
public:
	FileDetail(const std::string& path, const std::string& name,long long size);
	
	const std::string& path() const;
	const std::string& name() const;
	const std::string& type() const;
	const long long size() const;
	const int find_next() const;
	const std::string& md5() const;
	const std::string location() const;

private:
	std::string _path;
	std::string _name;
	std::string _md5; 
	long long _size;
	std::set<int> _blocks;//´æ´¢ÎÄ¼þ¿é
};