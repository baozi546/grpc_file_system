#include "Client.h"
#include <filesystem>
Client::Client(const std::string& ip)
{
	Auth_stub_ = std::make_unique<file_system::AuthService::Stub>(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()));
	File_stub_ = std::make_unique<file_system::FileService::Stub>(grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()));
}

bool Client::login(const std::string& username, const std::string& password, std::string& token)
{
    file_system::LoginRequest request;
    file_system::OperationResponse response;

    request.set_username(username);
    request.set_password(password);

    grpc::ClientContext context;
    grpc::Status status = Auth_stub_->Login(&context, request, &response);//·¢ËÍ
    if (status.ok()) {
        if (response.success()) {
            token = response.extensions();
            return true;
        }
        else {
            std::cout<<response.error_detail()<<std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
}

bool Client::Dir_Create(const std::string token, const std::string root_path, std::string name)
{
    file_system::FileOperationRequest request;
    file_system::OperationResponse response;

    file_system::CreateRequest* create_request = request.mutable_create_quest();
    create_request->set_root_path(root_path);
    create_request->set_name(name);

    grpc::ClientContext context;
    context.AddMetadata("token", token);
    grpc::Status status = File_stub_->FileOperation(&context, request, &response);
    if (status.ok()) {
        if (response.success()) {
            return true;
        }
        else {
            std::cout << response.error_detail() << std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
}

bool Client::File_Remove(const std::string token,file_system::FileMetadata file, const std::string& type)
{
    file_system::FileOperationRequest request;
    file_system::OperationResponse response;

    file_system::RemoveRequest* remove_request = request.mutable_remove_quest();
    remove_request->set_allocated_metedata(&file);
    grpc::ClientContext context;
    context.AddMetadata("token", token);
    grpc::Status status = File_stub_->FileOperation(&context, request, &response);
    if (status.ok()) {
        if (response.success()) {
            return true;
        }
        else {
            std::cout << response.error_detail() << std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
    return false;
}

bool Client::File_Rename(const std::string token, const std::string root_path, std::string old_name, std::string new_name, const std::string& type)
{
    file_system::FileOperationRequest request;
    file_system::OperationResponse response;

    file_system::ReNameRequest* rename_request = request.mutable_rename_quest();
    rename_request->set_root_path(root_path);
    rename_request->set_old_name(old_name);
    rename_request->set_new_name(new_name);
    rename_request->set_type(type);

    grpc::ClientContext context;
    context.AddMetadata("token", token);
    grpc::Status status = File_stub_->FileOperation(&context, request, &response);
    if (status.ok()) {
        if (response.success()) {
            return true;
        }
        else {
            std::cout << response.error_detail() << std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
    return false;
}

bool Client::Get_List(const std::string token, const std::string root_path, std::vector<file_system::FileMetadata>& list)
{
    file_system::GetFileListRequest request;
    grpc::ClientContext context;
    context.AddMetadata("token", token);
    auto streams = File_stub_->GetFileList(&context, request);
    file_system::FileMetadata file_metadata;

    while (streams->Read(&file_metadata)) {
        list.push_back(file_metadata);
    }
    if (streams->Finish().ok()) {
        return true;
        std::cout << "Get_List success" << std::endl;
    }
    else {
        std::cout << "Get_List failed" << std::endl;
    }
}

bool Client::Find_File(const std::string token, const std::string root_path, const std::string name, std::vector<file_system::FileMetadata>& list)
{
    file_system::FindFileRequest request;
    request.set_root_path(root_path);
    request.set_file_name(name);
    grpc::ClientContext context;
    context.AddMetadata("token", token);
    auto streams = File_stub_->FindFile(&context, request);
    file_system::FileMetadata file_metadata;
    while (streams->Read(&file_metadata)) {
        list.push_back(file_metadata);
    }
    streams->Finish();
    return false;
}


bool Client::UpTaskCreate(const std::string token, const file_system::FileMetadata& file, std::string& file_id)
{
    file_system::FileMetadata request = file;
    file_system::UploadFileResponse response;
    grpc::ClientContext context;
    context.AddMetadata("token", token);
    grpc::Status status = File_stub_->UploadFileRequest(&context,request, &response);
    if (status.ok()) {
        auto status_response = response.status();
        if (status_response.success()) {
            file_id = response.file_id();
            return true;
        }
        else {
            std::cout << status_response.error_detail() << std::endl;
            return false;
        }
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }
    return true;
}

bool Client::UpChunkStream(const std::string token, std::vector<file_system::FileChunk>& chunk_list , file_system::UploadStatus& resoonse)
{
    grpc::ClientContext context;
    context.AddMetadata("token", token);

    auto streams = File_stub_->UploadFile(&context, &resoonse);

    for (auto& chunk : chunk_list) {
        streams->Write(chunk);
    }
    streams->WritesDone();
    streams->Finish();
    auto status = resoonse.status();
    if (status.success()) {
        return true;
    }
    else {
        return false;
    }
    return false;
}

bool Client::MergeChunk(const std::string token, const file_system::FileMetadata& metedata , std::string& long_task_id)
{
    file_system::OperationResponse response;

    grpc::ClientContext context;
    context.AddMetadata("token", token);
    grpc::Status status = File_stub_->MergeChunkRequest(&context, metedata, &response);

    if (status.ok()) {
        if (response.success()) {
            long_task_id = response.extensions();
            return true;
        }
        else {
            std::cout << response.error_detail() << std::endl;
            return false;
        }
    }
    return false;
}

bool Client::DownTaskCreate(const std::string token, const file_system::FileMetadata& file, std::string& file_id)
{
    file_system::DownloadFileResponse response;
    grpc::ClientContext context;
    context.AddMetadata("token", token);

    grpc::Status status = File_stub_->DownloadFileRequest(&context, file, &response);

    if (status.ok()) {
        auto status_response = response.status();
        if (status_response.success()) {
            file_id = response.file_id();
            return true;
        }
        else {
            std::cout << status_response.error_detail() << std::endl;
            return false;
        }
    }
    return false;
}

bool Client::DownChunkStream(const std::string token, const file_system::FileRequest request, std::vector<file_system::FileChunk>& chunk_list)
{
    grpc::ClientContext context;
    context.AddMetadata("token", token);

    auto streams = File_stub_->DownloadFile(&context, request);
    file_system::FileChunk chunk;
    while (streams->Read(&chunk)) {
        chunk_list.push_back(chunk);
    }
    streams->Finish();
    return true;
}
