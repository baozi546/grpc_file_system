#include "FileServer.h"
#include <filesystem>
#include <fstream>
#include "tools.h"
#include "FileOperation.h"

#define Check_Username(username) {\
 if(username.empty()) return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid token"); \
}

bool Check_Filename(std::string filename) {                                          
  if (filename.empty())                                                     
    return 0; 
  const std::string invalid_chars = "/\\:*?\"<>|";                          
  if (filename.find_first_of(invalid_chars) != std::string::npos)          
    return 0;                  
  if (filename.length() > 255)                                              
    return 0;   
  if (filename[0] == '.')                                                   
    return 0;  
}

FileServer::FileServer() {
	m_random_task = std::make_shared<std::mt19937_64>(time(0));
	Read_Dir_Config();
}

void FileServer::Read_Dir_Config()
{
	m_dir_tree["root"] = std::make_shared<FileDirTree>("root");
}

bool FileServer::split_directory_path(const std::string& input_path, std::queue<std::string>& output)
{
	std::queue<std::string> components;

	try {
		// 将输入路径转换为 filesystem::path 对象（自动处理不同平台的分隔符）
		std::filesystem::path path_obj(input_path);

		// 规范化路径（处理"."、".."和冗余分隔符）
		path_obj = path_obj.lexically_normal();

		// 遍历路径组件
		for (const auto& comp : path_obj) {
			std::string str_comp = comp.string();

			// 跳过空根目录（处理绝对路径开头的"/"）
			if (str_comp.empty() && components.empty()) continue;

			components.push(str_comp);
		}
	}
	catch (...) {
		// 异常处理（如非法字符路径）
		return false;
	};
	output = components;
	return true;
}

bool FileServer::File_Update_Queue_Add(const std::string username, const::file_system::FileMetadata& metadata)
{
	return false;
}

bool FileServer::File_Chunk_Write(const std::string username, const file_system::FileChunk& chunk)
{
	auto detail = Update_File_Queue.get_Task(chunk.file_id());

	if (detail == nullptr) {
        return false;
	}

	if (!detail->modify_block(chunk.index() ,chunk.chunk_size())) {
		return false;
	}
	int ok = FileOperation::FileWrite(std::to_string(chunk.index()) + ".chunk", chunk.data(), UPDATE_PATH +  std::string("\\") + detail->get_mete_data()->_file_id);
	if (ok != 1)
	{
		return false;
	}
	return true;
}
bool FileServer::File_Download_Queue_Add(const std::string username, const file_system::FileMetadata& metadata)
{
	return false;
}
int FileServer::FileCreate(std::string username, const::file_system::CreateRequest& request, ::file_system::OperationResponse* response)
{

	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}

	if (root_path_ptr != nullptr) {
		std::string root_path = request.root_path();
		std::string dir_name = request.name();
		if (!Check_Filename(dir_name)) {
			response->set_success(false);
            response->set_error_detail("Invalid filename");
            return 0;
		}
		std::queue<std::string> path_components;

		split_directory_path(root_path, path_components);

		while (!path_components.empty()) {
			root_path_ptr = root_path_ptr->Get_child(path_components.front());
			if (root_path_ptr == nullptr) {
				LOG_ERROR("Dir Not Exist");
				response->set_success(false);
				response->set_error_detail("Dir Not Exist");
				return 0;
			}
			path_components.pop();
		}
		if (root_path_ptr->Create_dir(dir_name)) {
			LOG_INFO("Create Success");
			response->set_success(true);
			return 1;
		}
		else {
			LOG_ERROR("Create Failed");
			response->set_success(false);
			response->set_error_detail("Create Failed");
			return 0;
		}
	}
	else {
		LOG_ERROR("User not found");
		response->set_success(false);
		response->set_error_detail("User not found");
		return 0;
	}

	return 1;
}

int FileServer::FileRemove(std::string username, const::file_system::RemoveRequest& request, ::file_system::OperationResponse* response)
{
	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}

	if (root_path_ptr != nullptr) {
		auto metedata = request.metedata();
		std::string root_path = metedata.parent_path();
		std::string file_name = metedata.file_name();
		Check_Filename(file_name);
		std::queue<std::string> path_components;

		split_directory_path(root_path, path_components);

		while (!path_components.empty()) {
			root_path_ptr = root_path_ptr->Get_child(path_components.front());
			if (root_path_ptr == nullptr) {
				LOG_ERROR("Dir Not Exist");
				response->set_success(false);
				response->set_error_detail("Dir Not Exist");
				return 0;
			}
			path_components.pop();
		}

		if (metedata.extensions().contains("type") && metedata.extensions().at("type") == "Dir") {
			if (root_path_ptr->Remove_child(file_name)) {
				LOG_INFO("Remove Success");
				response->set_success(true);
				return 1;
			}
			else {
				LOG_ERROR("Remove Failed");
				response->set_success(false);
				response->set_error_detail("Create Failed");
				return 0;
			}
		}
		else if (metedata.extensions().contains("type") && metedata.extensions().at("type") == "File") {
			if (root_path_ptr->Remove_file(file_name)) {
				LOG_INFO("Remove Success");
				m_file.remove_Task(metedata.file_id());
				response->set_success(true);
				return 1;
			}
			else {
				LOG_ERROR("Remove Failed");
				response->set_success(false);
				response->set_error_detail("Create Failed");
				return 0;
			}
		}
	}
	else {
		LOG_ERROR("User not found");
		response->set_success(false);
		response->set_error_detail("User not found");
		return 0;
	}
	return 1;
}

int FileServer::FileRename(std::string username, const::file_system::ReNameRequest& request, ::file_system::OperationResponse* response)
{
	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}

	if (root_path_ptr != nullptr) {
		std::string root_path = request.root_path();
		std::string old_name = request.old_name();
		std::string file_name = request.new_name();
		Check_Filename(file_name);
		Check_Filename(old_name);
		std::queue<std::string> path_components;

		split_directory_path(root_path, path_components);

		while (!path_components.empty()) {
			root_path_ptr = root_path_ptr->Get_child(path_components.front());
			if (root_path_ptr == nullptr) {
				LOG_ERROR("Dir Not Exist");
				response->set_success(false);
				response->set_error_detail("Dir Not Exist");
				return 0;
			}
			path_components.pop();
		}

		if (request.type() == "Dir") {
			if (root_path_ptr->Rename_dir(old_name,file_name)) {
				LOG_INFO("Rename Success");
				response->set_success(true);
				return 1;
			}
			else {
				LOG_ERROR("Rename Failed");
				response->set_success(false);
				response->set_error_detail("Create Failed");
				return 0;
			}
		}
		else if (request.type() == "File") {
			if (root_path_ptr->Rename_file(old_name, file_name)) {
				LOG_INFO("Rename Success");
				response->set_success(true);
				return 1;
			}
			else {
				LOG_ERROR("Rename Failed");
				response->set_success(false);
				response->set_error_detail("Rename Failed");
				return 0;
			}
		}
		else {
            LOG_ERROR("Invalid Type");
            response->set_success(false);
            response->set_error_detail("Invalid Type");
			return 0;
		}
	}
	else {
		LOG_ERROR("User not found");
		response->set_success(false);
		response->set_error_detail("User not found");
		return 0;
	}
	return 1;
}

int FileServer::GetFileList(std::string username, const::file_system::GetFileListRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer)
{
	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}
	if (root_path_ptr != nullptr) {
		std::string root_path = request->root_path();
		std::queue<std::string> path_components;

		split_directory_path(root_path, path_components);

		while (!path_components.empty()) {
			root_path_ptr = root_path_ptr->Get_child(path_components.front());
			if (root_path_ptr == nullptr) {
				LOG_ERROR("Dir Not Exist");
				return 0;
			}
			path_components.pop();
		}
		auto file_list = root_path_ptr->Get_File_List();
		for (auto& child : file_list) {
			file_system::FileMetadata file_metadata;
			
			file_metadata.set_file_id(child.file_id);
			file_metadata.set_file_name(child.file_name);
			file_metadata.mutable_extensions()->insert({ "type",child.type == FileDirTree::FileDirTreeNode::FILE ? "File" : "Dir" });
			writer->Write(file_metadata);
		}
	}
	return 1;
}

int FileServer::FileFile(std::string username, const::file_system::FindFileRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer)
{
	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}
	if (root_path_ptr != nullptr) {

		if (request->has_root_path()) {//如存在指定目录
			std::string root_path = request->root_path();
			std::queue<std::string> path_components;
			split_directory_path(root_path, path_components);

			while (!path_components.empty()) {
				root_path_ptr = root_path_ptr->Get_child(path_components.front());
				if (root_path_ptr == nullptr) {
					LOG_ERROR("Dir Not Exist");
					return 0;
				}
				path_components.pop();
			}
		}

		std::string root_path = request->root_path();
		std::queue<std::shared_ptr<FileDirTree>> path_queue;

		auto paths = root_path_ptr->Get_child_list();
		for (auto& path : paths) {
			path_queue.push(path);
		}

		while (!paths.empty()) {
			root_path_ptr = path_queue.front();
			path_queue.pop();
			auto paths = root_path_ptr->Get_child_list();
			for (auto& path : paths) {
				path_queue.push(path);
			}
			auto file_list = root_path_ptr->Get_File_List();
			for (auto& child : file_list) {
				file_system::FileMetadata file_metadata;
				if (child.file_name.find(request->file_name()) != std::string::npos) {
					file_metadata.set_file_id(child.file_id);
					file_metadata.set_file_name(child.file_name);
					file_metadata.mutable_extensions()->insert({ "type",child.type == FileDirTree::FileDirTreeNode::FILE ? "File" : "Dir" });
					writer->Write(file_metadata);
				}
			}
		}
	}
	return 1;
}

int FileServer::FileUpTaskCreate(std::string username, const::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response)
{
	std::shared_ptr<FileDirTree> root_path_ptr = nullptr;
	auto status = response->mutable_status();

	auto find_ = m_dir_tree.find("root");
	if (find_ != m_dir_tree.end()) {
		root_path_ptr = find_->second;
	}
	if (root_path_ptr != nullptr) {
		std::string root_path = request->parent_path();
		std::queue<std::string> path_components;
		split_directory_path(root_path, path_components);

		while (!path_components.empty()) {
			root_path_ptr = root_path_ptr->Get_child(path_components.front());
			if (root_path_ptr == nullptr) {
				LOG_ERROR("Dir Not Exist");
				return 0;
			}
			path_components.pop();
		}
		if (root_path_ptr->File_exist(request->file_name())){
			status->set_success(false);
			status->set_error_detail("File Exist");
		}
	}
	std::shared_ptr<FileMeteData> metadata = std::make_shared<FileMeteData>();
	metadata->acctual_block_id = 1;
	std::string str_md5 = username + "\\" + request->parent_path() + "\\" + request->file_name();
	metadata->_file_id = tools::calculate_md5(str_md5.c_str(), str_md5.size());
	metadata->_name = request->file_name();
	metadata->_size = request->file_size();
	metadata->_owner = username;

	if (Update_File_Queue.get_Task(metadata->_file_id)) {
		status->set_success(false);
        status->set_error_detail("File UpTask Exist");
		return 0;
	}
	

	std::shared_ptr<FileDetail> detail = std::make_shared<FileDetail>(metadata);
	
	int ok = Update_File_Queue.add_Task(metadata->_file_id, detail);

	if (ok != 1) {
		status->set_success(false);
        status->set_error_detail("File UpTask Create Failed");
	}
	
	status->set_success(true);
	response->set_file_id(metadata->_file_id);
	return 1;
}

int FileServer::FileUpdateStream(std::string username, ::grpc::ServerReader<::file_system::FileChunk>* reader, ::file_system::UploadStatus* response)
{
    file_system::FileChunk chunk;
	auto chunk_map = response->mutable_chunk_status();
	auto status = response->mutable_status();
	int count = 0;
	bool error = false;
	while (reader->Read(&chunk)) {
		int ok = File_Chunk_Write(username, chunk);
		if (ok != 1)
		{
			error = true;
		}
		chunk_map->insert({ chunk.index(),ok == 1 ? true : false });
		count++;
	};
	if (error) {
		status->set_success(false);
		status->set_error_detail("File UpDate Error");
		return 0;
	}
	status->set_success(true);
	return 1;
}

int FileServer::FileMergeChunk(std::string username, const::file_system::FileMetadata* request, ::file_system::OperationResponse* response)
{
	auto file_id = request->file_id();
    auto detail = Update_File_Queue.get_Task(file_id);

	if (detail == nullptr) {
        response->set_success(false);
        response->set_error_detail("File UpTask Not Exist");
        return 0;
	}

	int ok = detail->set_merge();

	if (ok != 1) {
		response->set_success(false);
		response->set_error_detail("File Merge Error");
		return 0;
	}

	std::string md5_mid;
	if (request->extensions().contains("md5")) {
		md5_mid = request->extensions().at("md5");
	}else if (!detail->get_mete_data()->_md5.empty()) {
		md5_mid = detail->get_mete_data()->_md5;
	}
	std::shared_ptr<std::atomic_int> progress = std::make_shared<std::atomic_int>(0);
	auto mid_path = request->parent_path();
	auto task = [this, progress , detail , mid_path , md5_mid]() {
		std::string date;
		std::string tmp_path = UPDATE_PATH + std::string("\\") + detail->get_mete_data()->_file_id;
		std::string write_path = SAVE_PATH + std::string("\\") + detail->get_mete_data()->_file_id;

		auto blocks = detail->blocks();
		for (int i = 0; i < blocks.size(); i++) {
			std::string buffer;
			int ok = FileOperation::FileRead(std::to_string(i) + ".chunk", buffer, tmp_path);
			if (ok == -1) {
				progress->store(-1);
				return;
			}
			progress->store((i + 1) * 100 / blocks.size());
			date += buffer;
		}
		if (!md5_mid.empty()) {
			std::string md5 = tools::calculate_md5(date.c_str(), date.size());
			if (md5 != md5_mid) {
				progress->store(-1);
				return;
			}
		}
		int ok = FileOperation::FileWrite(detail->get_mete_data()->_name, date, write_path);
		if (ok != 1) {
			progress->store(-1);
			return;
		}

		std::shared_ptr<FileDirTree> root_path_ptr = nullptr;
		auto find_ = m_dir_tree.find(detail->get_mete_data()->_owner);
		if (find_ != m_dir_tree.end()) {
			root_path_ptr = find_->second;
		}
		if (root_path_ptr != nullptr) {
			std::string root_path;
			std::queue<std::string> path_components;
			split_directory_path(root_path, path_components);

			while (!path_components.empty()) {
				root_path_ptr = root_path_ptr->Get_child(path_components.front());
				if (root_path_ptr == nullptr) {
					progress->store(-1);
					return;
				}
				path_components.pop();
			}
			
			FileDirTree::FileDirTreeNode node;
			node.type = FileDirTree::FileDirTreeNode::FILE;

			std::shared_ptr<FileMeteData> metedata_ptr = detail->get_mete_data();

			node.file_id = metedata_ptr->_file_id;
            node.file_name = metedata_ptr->_name;
			
			m_file.add_Task(metedata_ptr->_file_id, metedata_ptr);
			root_path_ptr->Add_file(node);
		}
	};
	ThreadPool::Get().enqueue(task);
	response->set_success(true);
	return 1;
}

int FileServer::FileDownTaskCreate(std::string username, const::file_system::FileMetadata* request, ::file_system::DownloadFileResponse* response)
{	
	auto status = response->mutable_status();
	auto metedata = m_file.get_Task(request->file_id());
	if(metedata == nullptr) {
        status->set_success(false);
        status->set_error_detail("File Not Exist");
        return 0;
	}
    if (Download_File_Queue.get_Task(request->file_id())) {
        status->set_success(false);
        status->set_error_detail("File DownTask Exist");
        return 0;
    }

	std::ifstream file_stream(tools::StringToWString(SAVE_PATH + '/' + metedata->_file_id + '/' + metedata->_name), std::ios::binary);
	if (!file_stream.is_open()) {
        status->set_success(false);
        status->set_error_detail("File Not Exist");
	}
	char* buffer = new char[1024 * 1024 * 4];
	int index = 0;
	while(true) {
		file_stream.read(buffer, 1024 * 1024 * 4);
		int bytes_read = file_stream.gcount();
		if(bytes_read == 0) {
			break;
		}
		FileOperation::FileWrite(std::to_string(index) + ".chunk", std::string(buffer, bytes_read),DOWNLOAD_PATH + '/' + request->file_id());
	}

	delete[] buffer;
    status->set_success(true);
    response->set_file_id(request->file_id());
	Download_File_Queue.add_Task(request->file_id(), metedata);
	return 1;
}

int FileServer::FileDownloadStream(std::string username, const::file_system::FileRequest* request, ::grpc::ServerWriter<::file_system::FileChunk>* writer)
{
	auto metedata = Download_File_Queue.get_Task(request->file_id());
	if (metedata == nullptr) {
		return -1;
	}
	
	int block_size = (metedata->_size + (1024 * 1024 * 4 - 1)) / (1024 * 1024 * 4);
	int index = request->index();
	if(index > block_size || index < 0) {
		return -1;
	}
	file_system::FileChunk chunk;
	chunk.set_file_id(request->file_id());
	do {
		std::string data;
		int ok = FileOperation::FileRead(std::to_string(index) + ".chunk", data, DOWNLOAD_PATH + '/' + request->file_id());
		chunk.set_md5(tools::calculate_md5(data.c_str(), data.size()));
		chunk.set_index(index);
        chunk.set_data(data);
		index++;
	} while (writer->Write(chunk) && index < block_size);
	return 1;
}

::grpc::Status FileServer::FileOperation(::grpc::ServerContext* context, const::file_system::FileOperationRequest* request, ::file_system::OperationResponse* response)
{
    std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);
	file_system::FileOperationType type = request->type();

	/*for (const auto& kv : context->client_metadata()) {
		std::cout << "Key: " << kv.first << ", Value: "
			<< std::string(kv.second.data(), kv.second.size()) << std::endl;
	}*/
	int ok = -1;
	switch (type)
	{
	case file_system::CREATE:
        LOG_INFO("user: " + username + "，File_Create");
		ok = FileCreate(username, request->create_quest(), response);
		break;
	case file_system::REMOVE:
        LOG_INFO("user: " + username + "，File_Remove");
		ok = FileRemove(username, request->remove_quest(), response);
		break;
	case file_system::RENAME:
        LOG_INFO("user: " + username + "，File_Rename");
        ok = FileRename(username, request->rename_quest(), response);
		break;
	case file_system::COPY:
		break;
	case file_system::FileOperationType_INT_MIN_SENTINEL_DO_NOT_USE_:
		break;
	case file_system::FileOperationType_INT_MAX_SENTINEL_DO_NOT_USE_:
		break;
	default:
		break;
	}

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::UploadFileRequest(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::UploadFileResponse* response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	LOG_INFO("user: " + username + "，UploadFileRequest");

	int ok = FileUpTaskCreate(username, request, response);
	
	return ::grpc::Status::OK;
}

::grpc::Status FileServer::UploadFile(::grpc::ServerContext* context, ::grpc::ServerReader<::file_system::FileChunk>* reader, ::file_system::UploadStatus* response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	int ok = FileUpdateStream(username, reader, response);

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::DownloadFileRequest(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::DownloadFileResponse response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	auto status = response.mutable_status();

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::DownloadFile(::grpc::ServerContext* context, const::file_system::FileRequest* request, ::grpc::ServerWriter<::file_system::FileChunk>* writer)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	int ok = FileDownloadStream(username, request, writer);

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::CheckUploadStatus(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::UploadStatus* response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	auto status = response->mutable_status();

	auto metadata = Update_File_Queue.get_Task(request->file_id());
    if (metadata == nullptr) {
        status->set_success(false);
        status->set_error_detail("File Not Exist");
    }
    else {
        status->set_success(true);
        auto chunk_map = response->mutable_chunk_status();
		auto chunks = metadata->blocks();
        for (auto& [key,detail]:chunks) {
            chunk_map->insert({ key,detail.second});
        }
    }

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::MergeChunkRequest(::grpc::ServerContext* context, const::file_system::FileMetadata* request, ::file_system::OperationResponse* response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	int ok = FileMergeChunk(username, request, response);

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::FindFile(::grpc::ServerContext* context, const::file_system::FindFileRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	int ok = FileFile(username, request, writer);

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::GetFileList(::grpc::ServerContext* context, const::file_system::GetFileListRequest* request, ::grpc::ServerWriter<::file_system::FileMetadata>* writer)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);

	int ret = GetFileList(username, request, writer);

	return ::grpc::Status::OK;
}

::grpc::Status FileServer::ProgressCheck(::grpc::ServerContext* context, const::file_system::ProgressRequest* request, ::file_system::ProgressRespond* response)
{
	std::string username;
	GetMetadataValue(context->client_metadata(), "username", username);
	username = username.substr(1);
	Check_Username(username);



	return ::grpc::Status();
}



